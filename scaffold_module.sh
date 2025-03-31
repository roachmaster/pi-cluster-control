#!/bin/bash

TEMPLATE_DIR="templates"
ROOT_CMAKE="CMakeLists.txt"

print_intro() {
  echo "🧱 New Module Scaffolder"
  echo "------------------------"
}

parse_args() {
  MODULE="$1"
  shift
  LIB_MODE=false
  TEST_MODE=false

  while [[ $# -gt 0 ]]; do
    case "$1" in
      --lib) LIB_MODE=true ;;
      --test) TEST_MODE=true ;;
    esac
    shift
  done
}

validate_module_does_not_exist() {
  if [ -d "$MODULE" ]; then
    echo "❌ Module '$MODULE' already exists. Aborting."
    exit 1
  fi
}

create_module_directory() {
  mkdir -p "$MODULE"/{src,include}
  touch "$MODULE/include/.gitkeep"
}

generate_file() {
  local template_file="$1"
  local output_file="$2"

  if [ ! -f "$template_file" ]; then
    echo "❌ Missing template: $template_file"
    exit 1
  fi

  sed "s/{{MODULE_NAME}}/$MODULE/g" "$template_file" > "$output_file"
}

update_root_cmake() {
  if ! grep -q "add_subdirectory($MODULE)" "$ROOT_CMAKE"; then
    echo "add_subdirectory($MODULE)" >> "$ROOT_CMAKE"
    echo "✅ Module '$MODULE' added to root $ROOT_CMAKE"
  else
    echo "⚠️  '$MODULE' already exists in $ROOT_CMAKE"
  fi
}

scaffold_module_files() {
  if [ "$LIB_MODE" = true ]; then
    generate_file "$TEMPLATE_DIR/CMakeLists-lib.mustache" "$MODULE/CMakeLists.txt"
    generate_file "$TEMPLATE_DIR/class.cpp.mustache" "$MODULE/src/${MODULE}.cpp"
  else
    generate_file "$TEMPLATE_DIR/CMakeLists.txt.mustache" "$MODULE/CMakeLists.txt"
    generate_file "$TEMPLATE_DIR/main.cpp.mustache" "$MODULE/src/main.cpp"
  fi
}

scaffold_test_files() {
  local TEST_DIR="tests/${MODULE}_tests"
  mkdir -p "$TEST_DIR"

  generate_file "$TEMPLATE_DIR/test-CMakeLists.txt.mustache" "$TEST_DIR/CMakeLists.txt"
  generate_file "$TEMPLATE_DIR/test-main.cpp.mustache" "$TEST_DIR/test_main.cpp"
  generate_file "$TEMPLATE_DIR/test-module.cpp.mustache" "$TEST_DIR/test_${MODULE}.cpp"

  if ! grep -q "add_subdirectory(tests/${MODULE}_tests)" "$ROOT_CMAKE"; then
    echo "add_subdirectory(tests/${MODULE}_tests)" >> "$ROOT_CMAKE"
    echo "✅ Test module for '$MODULE' added to root $ROOT_CMAKE"
  fi
}

scaffold_module() {
  print_intro
  parse_args "$@"
  validate_module_does_not_exist
  create_module_directory
  scaffold_module_files
  update_root_cmake

  if [ "$TEST_MODE" = true ]; then
    scaffold_test_files
  fi

  echo "✅ Module '$MODULE' scaffolded successfully!"
}

# ── Entry Point ─────────────────────────────
if [ $# -lt 1 ]; then
  echo "Usage: ./scaffold_module.sh <module_name> [--lib] [--test]"
  exit 1
fi

scaffold_module "$@"
