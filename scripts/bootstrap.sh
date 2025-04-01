#!/bin/bash

# Prevent bootstrap.sh from being executed as a git hook symlink
if [[ "$0" == *".git/hooks/pre-commit"* ]]; then
  echo "❌ ERROR: bootstrap.sh should not be symlinked into .git/hooks. Use setup-hooks.sh to install properly."
  exit 1
fi

# Ensure everything resolves relative to the repo root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
MODULE_CONFIG="$ROOT_DIR/modules.yaml"
ROOT_CMAKE="$ROOT_DIR/CMakeLists.txt"
ALL_PRESENT=true

# Optional help flag
if [[ "$1" == "--help" ]]; then
  echo "Usage: ./scripts/bootstrap.sh"
  echo "Scans modules.yaml, regenerates CMake files, and validates dependencies."
  exit 0
fi

source "$SCRIPT_DIR/common.sh"

print_intro() {
  echo ""
  echo "$INFO  Verifying base environment for macOS..."
  echo "---------------------------------------------"
}

check_required_tools() {
  for tool in "${REQUIRED_TOOLS[@]}"; do
    if ! command -v "$tool" >/dev/null 2>&1; then
      echo "$FAIL Missing: $tool"
      echo "     Install with: brew install $tool"
      ALL_PRESENT=false
    else
      echo "$SUCCESS Found: $tool"
    fi
  done
}

check_module_packages() {
  echo ""
  echo "$INFO  Checking module-specific packages from $MODULE_CONFIG..."
  echo "---------------------------------------------"

  if [ ! -f "$MODULE_CONFIG" ]; then
    echo "$FAIL $MODULE_CONFIG not found. Skipping package checks."
    return
  fi

  mapfile -t packages < <(yq -r ".modules[].packages[]?" "$MODULE_CONFIG" | sort -u | uniq)

  for pkg in "${packages[@]}"; do
    if ! brew list --formula | grep -q "^$pkg$"; then
      echo "$FAIL Missing package: $pkg"
      echo "     Install with: brew install $pkg"
      ALL_PRESENT=false
    else
      echo "$SUCCESS Found package: $pkg"
    fi
  done
}

delete_and_regenerate_cmake_files() {
  echo ""
  echo "$INFO  Replacing all module-level CMakeLists.txt and test CMake files from templates..."
  echo "---------------------------------------------"

  local version=$(get_project_metadata "$MODULE_CONFIG" "version")
  local project_name=$(get_project_metadata "$MODULE_CONFIG" "project")

  if [ -z "$version" ] || [ -z "$project_name" ]; then
    echo "$FAIL Missing cmake.version or cmake.project in $MODULE_CONFIG."
    ALL_PRESENT=false
    return
  fi

  get_modules_json "$MODULE_CONFIG" | jq -c '.[]' | while read -r module; do
    local name=$(echo "$module" | jq -r '.name')
    local type=$(echo "$module" | jq -r '.type')
    local has_test=$(echo "$module" | jq -r '.test // false')

    local module_dir="$ROOT_DIR/$name"
    local cmake_file="$module_dir/CMakeLists.txt"
    local cmake_template="$(get_template_path CMakeLists.txt.mustache)"
    if [ "$type" == "lib" ]; then
      cmake_template="$(get_template_path CMakeLists-lib.mustache)"
    fi

    mkdir -p "$module_dir"
    rm -f "$cmake_file"

    render_template \
      "$(jq -n --arg name "$name" --arg version "$version" --arg project "$project_name" \
        '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project}')" \
      "$cmake_template" "$cmake_file"

    echo "$SUCCESS Regenerated $cmake_file"

    if [ "$has_test" == "true" ]; then
      local test_dir="$module_dir/test"
      local test_cmake="$test_dir/CMakeLists.txt"
      local test_template="$(get_template_path test-CMakeLists.txt.mustache)"

      mkdir -p "$test_dir"
      rm -f "$test_cmake"

      render_template \
        "$(jq -n --arg name "$name" --arg version "$version" --arg project "$project_name" \
          '{MODULE_NAME: $name, CMAKE_VERSION: $version, CMAKE_PROJECT: $project}')" \
        "$test_template" "$test_cmake"

      echo "$SUCCESS Regenerated $test_cmake"
    fi
  done

  echo ""
  echo "$INFO  Summary of modules:"
  get_modules_json "$MODULE_CONFIG" | jq -r '.[] | " - \(.name) (\(.type)) [test=\(.test // false)]"'
}

update_root_cmake() {
  echo ""
  echo "$INFO  Regenerating root CMakeLists.txt from template..."
  echo "---------------------------------------------"

  local version=$(get_project_metadata "$MODULE_CONFIG" "version")
  local project_name=$(get_project_metadata "$MODULE_CONFIG" "project")

  if [ -z "$version" ] || [ -z "$project_name" ]; then
    echo "$FAIL Missing cmake.version or cmake.project in $MODULE_CONFIG."
    ALL_PRESENT=false
    return
  fi

  local modules_json=$(get_modules_json "$MODULE_CONFIG" | \
    jq '[.[] | {
      NAME: .name,
      HAS_TEST: (.test // false)
    }]')

  local template_data=$(jq -n \
    --arg version "$version" \
    --arg project "$project_name" \
    --argjson modules "$modules_json" \
    '{ CMAKE_VERSION: $version, CMAKE_PROJECT: $project, MODULES: $modules }')

  render_template "$template_data" "$(get_template_path root-CMakeLists.txt.mustache)" "$ROOT_CMAKE"

  echo "$SUCCESS Root CMakeLists.txt fully regenerated from template."
}

report_final_status() {
  echo "---------------------------------------------"
  if [ "$ALL_PRESENT" = true ]; then
    echo "$DONE Environment is fully ready."
    exit 0
  else
    echo "$FAIL Some dependencies are missing. Please fix and retry."
    exit 1
  fi
}

# ── Entry Point ─────────────────────────────
print_intro
check_required_tools
check_module_packages
delete_and_regenerate_cmake_files
update_root_cmake
report_final_status
