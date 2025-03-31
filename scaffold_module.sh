#!/bin/bash

ROOT_CMAKE="CMakeLists.txt"
TEMPLATE_DIR="templates"
MODULE_CONFIG="modules.yaml"

SUCCESS="✅"
FAIL="❌"
INFO="🔧"

UPDATE_MODE=false

print_intro() {
  echo "\n$INFO  Running module scaffolder via $MODULE_CONFIG..."
  echo "---------------------------------------------"
}

parse_flags() {
  while [[ $# -gt 0 ]]; do
    case "$1" in
      --update) UPDATE_MODE=true ;;
    esac
    shift
  done
}

check_config_file_exists() {
  if [ ! -f "$MODULE_CONFIG" ]; then
    echo "$FAIL Missing $MODULE_CONFIG. Aborting."
    exit 1
  fi
}

create_module_structure() {
  local MODULE_NAME="$1"
  mkdir -p "$MODULE_NAME"/{src,include}
  touch "$MODULE_NAME/include/.gitkeep"
}

generate_file() {
  local template_file="$1"
  local output_file="$2"
  local module_name="$3"

  if [ ! -f "$template_file" ]; then
    echo "$FAIL Missing template: $template_file"
    exit 1
  fi

  if [ -f "$output_file" ] && [ "$UPDATE_MODE" = false ]; then
    echo "⚠️  Skipping existing: $output_file"
    return
  fi

  sed "s/{{MODULE_NAME}}/$module_name/g" "$template_file" > "$output_file"
  echo "$SUCCESS Created: $output_file"
}

update_root_cmake() {
  local MODULE_NAME="$1"
  if ! grep -q "add_subdirectory($MODULE_NAME)" "$ROOT_CMAKE"; then
    echo "add_subdirectory($MODULE_NAME)" >> "$ROOT_CMAKE"
    echo "$SUCCESS Added $MODULE_NAME to $ROOT_CMAKE"
  fi
}

scaffold_module() {
  local MODULE_NAME="$1"
  local MODULE_TYPE="$2"
  local MODULE_TEST="$3"

  echo "\n📦 Scaffolding: $MODULE_NAME ($MODULE_TYPE)"

  create_module_structure "$MODULE_NAME"

  if [ "$MODULE_TYPE" == "lib" ]; then
    generate_file "$TEMPLATE_DIR/CMakeLists-lib.mustache" "$MODULE_NAME/CMakeLists.txt" "$MODULE_NAME"
    generate_file "$TEMPLATE_DIR/class.cpp.mustache" "$MODULE_NAME/src/${MODULE_NAME}.cpp" "$MODULE_NAME"
  else
    generate_file "$TEMPLATE_DIR/CMakeLists.txt.mustache" "$MODULE_NAME/CMakeLists.txt" "$MODULE_NAME"
    generate_file "$TEMPLATE_DIR/main.cpp.mustache" "$MODULE_NAME/src/main.cpp" "$MODULE_NAME"
  fi

  if [ "$MODULE_TEST" = true ]; then
    local TEST_DIR="tests/${MODULE_NAME}_tests"
    mkdir -p "$TEST_DIR"
    generate_file "$TEMPLATE_DIR/test-CMakeLists.txt.mustache" "$TEST_DIR/CMakeLists.txt" "$MODULE_NAME"
    generate_file "$TEMPLATE_DIR/test-main.cpp.mustache" "$TEST_DIR/test_main.cpp" "$MODULE_NAME"
    generate_file "$TEMPLATE_DIR/test-module.cpp.mustache" "$TEST_DIR/test_${MODULE_NAME}.cpp" "$MODULE_NAME"
    if ! grep -q "add_subdirectory(tests/${MODULE_NAME}_tests)" "$ROOT_CMAKE"; then
      echo "add_subdirectory(tests/${MODULE_NAME}_tests)" >> "$ROOT_CMAKE"
      echo "$SUCCESS Added test module for $MODULE_NAME to $ROOT_CMAKE"
    fi
  fi

  update_root_cmake "$MODULE_NAME"
}

scaffold_all_modules() {
  local COUNT=0
  local MODULES=$(yq '.modules[]' "$MODULE_CONFIG")

  yq -o=json '.modules[]' "$MODULE_CONFIG" | jq -c '.' | while read -r module; do
    local NAME=$(echo "$module" | jq -r '.name')
    local TYPE=$(echo "$module" | jq -r '.type')
    local TEST=$(echo "$module" | jq -r '.test // false')

    scaffold_module "$NAME" "$TYPE" "$TEST"
    COUNT=$((COUNT + 1))
  done

  echo "\n$SUCCESS $COUNT modules scaffolded."
}

# ── Entry Point ─────────────────────────────
print_intro
parse_flags "$@"
check_config_file_exists
scaffold_all_modules