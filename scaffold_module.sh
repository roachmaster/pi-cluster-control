#!/bin/bash

SUCCESS="✅"
FAIL="❌"
INFO="🔍"
DONE="🎉"

MODULE_CONFIG="modules.yaml"
TEMPLATE_DIR="templates"

print_intro() {
  echo ""
  echo "$INFO  Scaffolding modules from $MODULE_CONFIG..."
  echo "---------------------------------------------"
}

create_directory_structure() {
  local name="$1"
  mkdir -p "$name/include" "$name/src"
}

generate_cmake_file() {
  local name="$1" type="$2" version="$3" project_name="$4"
  local cmake_template="$TEMPLATE_DIR/CMakeLists.txt.mustache"
  if [ "$type" == "lib" ]; then
    cmake_template="$TEMPLATE_DIR/CMakeLists-lib.mustache"
  fi
  if [ ! -f "$name/CMakeLists.txt" ]; then
    sed -e "s/{{MODULE_NAME}}/$name/g" \
        -e "s/{{CMAKE_VERSION}}/$version/g" \
        -e "s/{{CMAKE_PROJECT}}/$project_name/g" \
        "$cmake_template" > "$name/CMakeLists.txt"
    echo "$SUCCESS Created $name/CMakeLists.txt"
  fi
}

generate_main_cpp() {
  local name="$1"
  if [ ! -f "$name/src/main.cpp" ]; then
    sed "s/{{MODULE_NAME}}/$name/g" "$TEMPLATE_DIR/main.cpp.mustache" > "$name/src/main.cpp"
    echo "$SUCCESS Created $name/src/main.cpp"
  fi
}

generate_test_files() {
  local name="$1" version="$2" project_name="$3"
  mkdir -p "$name/test"
  if [ ! -f "$name/test/CMakeLists.txt" ]; then
    sed -e "s/{{MODULE_NAME}}/$name/g" \
        -e "s/{{CMAKE_VERSION}}/$version/g" \
        -e "s/{{CMAKE_PROJECT}}/$project_name/g" \
        "$TEMPLATE_DIR/test-CMakeLists.txt.mustache" > "$name/test/CMakeLists.txt"
    echo "$SUCCESS Created $name/test/CMakeLists.txt"
  fi
}

generate_feature_file() {
  local name="$1"
  local feature_dir="features/$name"
  local feature_file="$feature_dir/$name.feature"
  mkdir -p "$feature_dir/steps"
  if [ ! -f "$feature_file" ]; then
    sed "s/{{MODULE_NAME}}/$name/g" "$TEMPLATE_DIR/feature.mustache" > "$feature_file"
    echo "$SUCCESS Created $feature_file"
  fi
}

scaffold_modules() {
  local version=$(yq -r ".cmake.version" "$MODULE_CONFIG")
  local project_name=$(yq -r ".cmake.project" "$MODULE_CONFIG")

  yq -o=json ".modules[]" "$MODULE_CONFIG" | jq -c '.' | while read -r module; do
    local name=$(echo "$module" | jq -r '.name')
    local type=$(echo "$module" | jq -r '.type')
    local has_test=$(echo "$module" | jq -r '.test // false')

    create_directory_structure "$name"
    generate_cmake_file "$name" "$type" "$version" "$project_name"
    generate_main_cpp "$name"
    if [ "$has_test" == "true" ]; then
      generate_test_files "$name" "$version" "$project_name"
    fi
    generate_feature_file "$name"
  done
}

# ── Entry Point ─────────────────────────────
print_intro
scaffold_modules
