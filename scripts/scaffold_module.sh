#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/common.sh"

MODULE_CONFIG="$ROOT_DIR/modules.yaml"
ONLY_CMAKE=false
DRY_RUN=false

while [[ $# -gt 0 ]]; do
  case "$1" in
    --only-cmake) ONLY_CMAKE=true; shift ;;
    --dry-run) DRY_RUN=true; shift ;;
    *) echo "$FAIL Unknown argument: $1"; exit 1 ;;
  esac
done

pascal_case() {
  python3 -c "import sys; print(''.join(w.capitalize() for w in sys.argv[1].split('_')))" "$1"
}

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

  echo "$INFO Rendering template: $template"
  echo "$INFO ➜ Output file: $output"
  if $DRY_RUN; then
    echo "🔍 Would render using JSON:"
    echo "$json" | jq .
  else
    render_template "$json" "$template" "$output"
    echo "$SUCCESS Created $output"
  fi
}

create_directory_structure() {
  local name="$1"
  echo "$INFO Creating directory structure for $name"
  mkdir -p "$ROOT_DIR/$name/include" "$ROOT_DIR/$name/src"
}

generate_main_cpp() {
  local name="$1"
  local class_name
  echo "⚙️ Raw name for pascal_case: ${name}_app"
  class_name="$(pascal_case "${name}_app")"
  echo "⚙️ pascal_case name : $class_name"

  local interface_header="${name}.hpp"
  local factory_header="${name}_factory.hpp"

  echo "$INFO Generating main.cpp and adapter stubs for $name"

  local base_json
  base_json=$(jq -n \
    --arg name "$name" \
    --arg class "$class_name" \
    --arg interface "$interface_header" \
    --arg factory "$factory_header" \
    '{MODULE_NAME: $name, MODULE_CLASS: $class, MODULE_INTERFACE: $interface, MODULE_FACTORY: $factory}')
  echo "leo look:\n $base_json"
  maybe_render "$base_json" "$(get_template_path main.cpp.mustache)" "$ROOT_DIR/$name/src/main.cpp"
  maybe_render "$base_json" "$(get_template_path module_interface.hpp.mustache)" "$ROOT_DIR/$name/include/$interface_header"
  maybe_render "$base_json" "$(get_template_path module_interface_factory.hpp.mustache)" "$ROOT_DIR/$name/include/$factory_header"
  maybe_render "$base_json" "$(get_template_path module_impl.cpp.mustache)" "$ROOT_DIR/$name/src/${name}.cpp"
}

generate_class_stub() {
  local name="$1"
  echo "$INFO Generating class stubs for $name"
  maybe_render "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
    "$(get_template_path class.cpp.mustache)" "$ROOT_DIR/$name/src/${name}.cpp"
  maybe_render "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
    "$(get_template_path class.hpp.mustache)" "$ROOT_DIR/$name/include/${name}.hpp"
}

generate_cmake_file() {
  local name="$1" type="$2" version="$3" project_name="$4"
  echo "$INFO Generating CMakeLists.txt for $name"
  local template="$(get_template_path CMakeLists.txt.mustache)"
  [ "$type" == "lib" ] && template="$(get_template_path CMakeLists-lib.mustache)"

  maybe_render "$(jq -n --arg name "$name" --arg version "$version" --arg project "$project_name" \
    '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project}')" \
    "$template" "$ROOT_DIR/$name/CMakeLists.txt"
}

generate_test_files() {
  local name="$1" version="$2" project_name="$3"
  echo "$INFO Generating test support for $name"
  local test_dir="$ROOT_DIR/$name/test"
  mkdir -p "$test_dir"

  local deps=$(yq -o=json '.GLOBAL_TEST_PACKAGES' "$MODULE_CONFIG")
  local cxx=$(get_project_metadata "$MODULE_CONFIG" "CXX_STANDARD")

  local data=$(jq -n \
    --arg name "$name" \
    --arg version "$version" \
    --arg project "$project_name" \
    --argjson deps "$deps" \
    --arg cxx "$cxx" \
    '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project, CXX_STANDARD: $cxx|tonumber, GLOBAL_TEST_PACKAGES: $deps}')

  maybe_render "$data" "$(get_template_path test-CMakeLists.txt.mustache)" "$test_dir/CMakeLists.txt"
  maybe_render "$(jq -n --arg name "$name" '{MODULE_NAME: $name}')" \
    "$(get_template_path test-main.cpp.mustache)" "$test_dir/test_main.cpp"
}

generate_feature_meta() {
  echo ""
  echo "$INFO  Generating feature metadata from BDD files..."
  echo "---------------------------------------------"

  local BDD_SCRIPT="$ROOT_DIR/scripts/convert_bdd.sh"
  [[ ! -f "$BDD_SCRIPT" ]] && echo "$FAIL Missing: $BDD_SCRIPT" && exit 1

  get_modules_json "$MODULE_CONFIG" | jq -c '.[]' | while read -r module; do
    local name=$(echo "$module" | jq -r '.NAME')
    local type=$(echo "$module" | jq -r '.TYPE')

    [[ "$type" =~ exe|lib ]] || continue
    local dir="$ROOT_DIR/features/$name"
    [[ ! -d "$dir" ]] && continue

    echo "$INFO  Processing features in: $dir"
    for bdd_file in "$dir"/*.bdd; do
      [[ -f "$bdd_file" ]] || continue
      echo "$INFO  ➜ Converting $bdd_file"
      bash "$BDD_SCRIPT" "$bdd_file"
    done
  done
}

generate_feature_tests() {
  local name="$1"
  echo "$INFO  Rendering BDD test files for $name"
  local feature_dir="$ROOT_DIR/features/$name"
  local test_dir="$ROOT_DIR/$name/test"
  mkdir -p "$test_dir"

  local template_path
  template_path="$(get_template_path bdd_test_cpp.mustache)"

  for json_file in "$feature_dir"/*.json; do
    [[ -f "$json_file" ]] || continue
    local base_name
    base_name=$(basename "$json_file" .json)
    local output="$test_dir/test_${base_name}.cpp"

    echo "$INFO    ➜ $json_file → $output"
    if ! render_template "$(cat "$json_file")" "$template_path" "$output"; then
      echo "$FAIL Failed to render template for $json_file"
    fi
  done

  echo "$SUCCESS Done rendering BDD tests for $name"
}

generate_modules_feature_tests() {
  echo ""
  echo "$INFO  Rendering BDD-based feature tests for all modules..."
  echo "---------------------------------------------"

  get_modules_json "$MODULE_CONFIG" | jq -c '.[]' | while read -r module; do
    local name=$(echo "$module" | jq -r '.NAME')
    local type=$(echo "$module" | jq -r '.TYPE')
    echo "$INFO DEBUG: type=$type for module $name"
    [[ "$type" =~ exe|lib ]] && generate_feature_tests "$name"
    echo "$INFO DEBUG: type=$type for module $name completed"
  done

  echo "$SUCCESS Finished rendering all BDD-based feature tests."
}

scaffold_modules() {
  echo ""
  echo "$INFO  Creating source tree for modules..."
  echo "---------------------------------------------"

  local version=$(get_project_metadata "$MODULE_CONFIG" "VERSION")
  local project=$(get_project_metadata "$MODULE_CONFIG" "PROJECT")

  get_modules_json "$MODULE_CONFIG" | jq -c '.[]' | while read -r module; do
    local name=$(echo "$module" | jq -r '.NAME')
    local type=$(echo "$module" | jq -r '.TYPE')
    local has_test=$(echo "$module" | jq -r '.TEST // false')

    echo "$INFO Processing module: $name ($type)"
    create_directory_structure "$name"
    generate_cmake_file "$name" "$type" "$version" "$project"
    echo "$INFO DEBUG: has_test=$has_test, type=$type for module $name"

    [[ "$type" == "exe" ]] && generate_main_cpp "$name"
    [[ "$type" == "lib" ]] && generate_class_stub "$name"
    generate_test_files "$name" "$version" "$project"
    echo "$INFO : done generating test dir has_test=$has_test, type=$type for module $name"
  done
}

cleanup_feature_meta() {
  echo ""
  echo "$INFO  Cleaning up generated YAML and JSON metadata in features/..."
  echo "---------------------------------------------"

  local feature_dir="$ROOT_DIR/features"
  if [[ ! -d "$feature_dir" ]]; then
    echo "$FAIL features directory not found at $feature_dir"
    return 1
  fi

  local files
  files=$(find "$feature_dir" \( -name '*.yaml' -o -name '*.json' \) -type f)
  local count
  count=$(echo "$files" | grep -c . || true)

  if [[ "$count" -eq 0 ]]; then
    echo "$INFO No metadata files found for cleanup."
    return 0
  fi

  echo "$INFO Found $count files to delete:"
  echo "$files"

  while read -r file; do
    echo "$INFO ➜ Deleting $file"
    rm -f "$file"
  done <<< "$files"

  echo "$SUCCESS Deleted $count metadata files."
}

# ── Run All Steps ──────────────────────────
print_intro
scaffold_modules
generate_feature_meta
generate_modules_feature_tests
cleanup_feature_meta
