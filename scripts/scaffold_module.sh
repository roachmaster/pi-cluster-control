#!/bin/bash
set -e

# ── Resolve Root Path from common.sh ─────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/common.sh"

MODULE_CONFIG="$ROOT_DIR/modules.yaml"
ONLY_CMAKE=false
DRY_RUN=false

# ── Parse Arguments ──────────────────────────────────────────
while [[ $# -gt 0 ]]; do
  case "$1" in
    --only-cmake) ONLY_CMAKE=true; shift ;;
    --dry-run) DRY_RUN=true; shift ;;
    *) echo "$FAIL Unknown argument: $1"; exit 1 ;;
  esac
done

print_intro() {
  echo ""
  echo "$INFO  Scaffolding modules from $MODULE_CONFIG..."
  echo "Options: ONLY_CMAKE=$ONLY_CMAKE, DRY_RUN=$DRY_RUN"
  echo "---------------------------------------------"
}

maybe_render() {
  local json="$1"
  local template="$2"
  local output="$3"

  if $DRY_RUN; then
    echo "🔍 Would render $output using template $template"
  else
    render_template "$json" "$template" "$output"
    echo "$SUCCESS Created $output"
  fi
}

create_directory_structure() {
  local name="$1"
  if $DRY_RUN; then
    echo "🔍 Would create: $ROOT_DIR/$name/include, $ROOT_DIR/$name/src"
  else
    mkdir -p "$ROOT_DIR/$name/include" "$ROOT_DIR/$name/src"
  fi
}

generate_cmake_file() {
  local name="$1" type="$2" version="$3" project_name="$4"
  local cmake_path="$ROOT_DIR/$name/CMakeLists.txt"
  local template_file="$(get_template_path CMakeLists.txt.mustache)"
  if [ "$type" == "lib" ]; then
    template_file="$(get_template_path CMakeLists-lib.mustache)"
  fi

  if [ ! -f "$cmake_path" ] || $DRY_RUN; then
    maybe_render \
      "$(jq -n --arg name "$name" --arg version "$version" --arg project "$project_name" \
        '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project}')" \
      "$template_file" "$cmake_path"
  fi
}

generate_main_cpp() {
  local name="$1"
  local output="$ROOT_DIR/$name/src/main.cpp"
  local template_file="$(get_template_path main.cpp.mustache)"

  if [ ! -f "$output" ] || $DRY_RUN; then
    maybe_render \
      "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
      "$template_file" "$output"
  fi
}

generate_class_stub() {
  local name="$1"
  local src_file="$ROOT_DIR/$name/src/${name}.cpp"
  local hpp_file="$ROOT_DIR/$name/include/${name}.hpp"
  local template_cpp="$(get_template_path class.cpp.mustache)"
  local template_hpp="$(get_template_path class.hpp.mustache)"

  if [ ! -f "$src_file" ] || $DRY_RUN; then
    maybe_render "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" "$template_cpp" "$src_file"
  fi

  if [ ! -f "$hpp_file" ] || $DRY_RUN; then
    maybe_render "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" "$template_hpp" "$hpp_file"
  fi
}
generate_test_files() {
  local name="$1" version="$2" project_name="$3"
  local test_dir="$ROOT_DIR/$name/test"
  local test_cmake="$test_dir/CMakeLists.txt"
  local test_main="$test_dir/test_main.cpp"
  local cxx_standard=$(get_project_metadata "$MODULE_CONFIG" "CXX_STANDARD")
  local test_deps=$(yq -o=json '.GLOBAL_TEST_PACKAGES' "$MODULE_CONFIG")

  echo "$INFO Generating test files for module: $name"
  echo "      Version: $version, Project: $project_name"
  echo "      CXX_STANDARD: $cxx_standard"
  echo "      Test dependencies: $test_deps"
  echo "      Target test CMake file: $test_cmake"

  if $DRY_RUN; then
    echo "🔍 Would create test dir: $test_dir"
  else
    mkdir -p "$test_dir"
  fi

  local template_data
  template_data=$(jq -n \
    --arg name "$name" \
    --arg version "$version" \
    --arg project "$project_name" \
    --argjson deps "$test_deps" \
    --arg cxx "$cxx_standard" \
    '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project, CXX_STANDARD: $cxx|tonumber, GLOBAL_TEST_PACKAGES: $deps}')

  echo "$INFO Rendering test CMake with data:"
  echo "$template_data" | jq .

  maybe_render \
    "$template_data" \
    "$(get_template_path test-CMakeLists.txt.mustache)" "$test_cmake"

  maybe_render \
    "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
    "$(get_template_path test-main.cpp.mustache)" "$test_main"
}

generate_feature_file() {
  local name="$1"
  local feature_dir="$ROOT_DIR/features/$name"
  local feature_file="$feature_dir/$name.feature"
  local template_file="$(get_template_path feature.mustache)"

  if $DRY_RUN; then
    echo "🔍 Would create: $feature_file"
  else
    mkdir -p "$feature_dir/steps"
  fi

  if [ ! -f "$feature_file" ] || $DRY_RUN; then
    maybe_render \
      "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
      "$template_file" "$feature_file"
  fi
}

scaffold_modules() {
  local version project_name
  version=$(get_project_metadata "$MODULE_CONFIG" "VERSION")
  project_name=$(get_project_metadata "$MODULE_CONFIG" "PROJECT")

  get_modules_json "$MODULE_CONFIG" | jq -c '.[]' | while read -r module; do
    local name=$(echo "$module" | jq -r '.NAME')
    local type=$(echo "$module" | jq -r '.TYPE')
    local has_test=$(echo "$module" | jq -r '.TEST // false')

    create_directory_structure "$name"
    generate_cmake_file "$name" "$type" "$version" "$project_name"

    if ! $ONLY_CMAKE; then
      if [ "$type" == "exe" ]; then
        generate_main_cpp "$name"
      elif [ "$type" == "lib" ]; then
        generate_class_stub "$name"
      fi

      if [ "$has_test" == "true" ]; then
        generate_test_files "$name" "$version" "$project_name"
      fi

      generate_feature_file "$name"
    fi
  done
}

# ── Entry Point ─────────────────────────────
print_intro
scaffold_modules
