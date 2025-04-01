#!/bin/bash

source "$(dirname "$0")/common.sh"

ROOT_DIR="$(dirname "$0")/.."
MODULE_CONFIG="$ROOT_DIR/modules.yaml"

print_intro() {
  echo ""
  echo "$INFO  Scaffolding modules from $MODULE_CONFIG..."
  echo "---------------------------------------------"
}

create_directory_structure() {
  local name="$1"
  mkdir -p "$ROOT_DIR/$name/include" "$ROOT_DIR/$name/src"
}

generate_cmake_file() {
  local name="$1" type="$2" version="$3" project_name="$4"

  local template_file="$(get_template_path CMakeLists.txt.mustache)"
  if [ "$type" == "lib" ]; then
    template_file="$(get_template_path CMakeLists-lib.mustache)"
  fi

  local cmake_path="$ROOT_DIR/$name/CMakeLists.txt"
  if [ ! -f "$cmake_path" ]; then
    render_template \
      "$(jq -n --arg name "$name" --arg version "$version" --arg project "$project_name" \
        '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project}')" \
      "$template_file" "$cmake_path"
    echo "$SUCCESS Created $cmake_path"
  fi
}

generate_main_cpp() {
  local name="$1"
  local output="$ROOT_DIR/$name/src/main.cpp"
  local template_file="$(get_template_path main.cpp.mustache)"

  if [ ! -f "$output" ]; then
    render_template \
      "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
      "$template_file" "$output"
    echo "$SUCCESS Created $output"
  fi
}

generate_class_stub() {
  local name="$1"
  local src_file="$ROOT_DIR/$name/src/${name}.cpp"
  local hpp_file="$ROOT_DIR/$name/include/${name}.hpp"
  local template_cpp="$(get_template_path class.cpp.mustache)"
  local template_hpp="$(get_template_path class.hpp.mustache)"

  if [ ! -f "$src_file" ]; then
    render_template "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" "$template_cpp" "$src_file"
    echo "$SUCCESS Created $src_file"
  fi

  if [ ! -f "$hpp_file" ]; then
    render_template "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" "$template_hpp" "$hpp_file"
    echo "$SUCCESS Created $hpp_file"
  fi
}

generate_test_files() {
  local name="$1" version="$2" project_name="$3"
  local test_dir="$ROOT_DIR/$name/test"
  local test_cmake="$test_dir/CMakeLists.txt"
  local test_main="$test_dir/test_main.cpp"
  local test_module="$test_dir/test_${name}.cpp"

  mkdir -p "$test_dir"

  if [ ! -f "$test_cmake" ]; then
    render_template \
      "$(jq -n --arg name "$name" --arg version "$version" --arg project "$project_name" \
        '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project}')" \
      "$(get_template_path test-CMakeLists.txt.mustache)" "$test_cmake"
    echo "$SUCCESS Created $test_cmake"
  fi

  if [ ! -f "$test_main" ]; then
    cp "$(get_template_path test-main.cpp.mustache)" "$test_main"
    echo "$SUCCESS Created $test_main"
  fi

  if [ ! -f "$test_module" ]; then
    render_template \
      "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
      "$(get_template_path test-module.cpp.mustache)" "$test_module"
    echo "$SUCCESS Created $test_module"
  fi
}

generate_feature_file() {
  local name="$1"
  local feature_dir="$ROOT_DIR/features/$name"
  local feature_file="$feature_dir/$name.feature"
  local template_file="$(get_template_path feature.mustache)"

  mkdir -p "$feature_dir/steps"

  if [ ! -f "$feature_file" ]; then
    render_template \
      "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
      "$template_file" "$feature_file"
    echo "$SUCCESS Created $feature_file"
  fi
}

scaffold_modules() {
  local version
  local project_name
  version=$(get_project_metadata "$MODULE_CONFIG" "version")
  project_name=$(get_project_metadata "$MODULE_CONFIG" "project")

  get_modules_json "$MODULE_CONFIG" | jq -c '.[]' | while read -r module; do
    local name
    local type
    local has_test
    name=$(echo "$module" | jq -r '.name')
    type=$(echo "$module" | jq -r '.type')
    has_test=$(echo "$module" | jq -r '.test // false')

    create_directory_structure "$name"
    generate_cmake_file "$name" "$type" "$version" "$project_name"

    if [ "$type" == "exe" ]; then
      generate_main_cpp "$name"
    elif [ "$type" == "lib" ]; then
      generate_class_stub "$name"
    fi

    if [ "$has_test" == "true" ]; then
      generate_test_files "$name" "$version" "$project_name"
    fi

    generate_feature_file "$name"
  done
}

# ── Entry Point ─────────────────────────────
print_intro
scaffold_modules
