#!/usr/bin/env bash

# Prevent bootstrap.sh from being executed as a git hook symlink
if [[ "$0" == *".git/hooks/pre-commit"* ]]; then
  echo "❌ ERROR: bootstrap.sh should not be symlinked into .git/hooks. Use setup-hooks.sh to install properly."
  exit 1
fi

# ── Resolve Paths and Shared Logic ─────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
TOOL_CONFIG="$ROOT_DIR/config/tools.yaml"
MODULE_CONFIG="$ROOT_DIR/modules.yaml"
ROOT_CMAKE="$ROOT_DIR/CMakeLists.txt"
ALL_PRESENT=true

source "$SCRIPT_DIR/common.sh"

# ── Bash Version Enforcement ───────────────────────────────────
required_bash_version=$(yq -r '.REQUIRED_TOOLS[] | select(.name == "bash") | .version' "$TOOL_CONFIG")
required_bash_major="${required_bash_version%%.*}"
current_bash_major="${BASH_VERSINFO[0]}"

if [[ "$current_bash_major" -lt "$required_bash_major" ]]; then
  echo "❌ Bash version $required_bash_version or higher is required. Current version: $BASH_VERSION"
  suggest_install "bash"
  exit 1
fi

# ── Intro ──────────────────────────────────────────────────────
print_intro() {
  echo ""
  echo "$INFO  Verifying base environment for macOS..."
  echo "---------------------------------------------"
}

# ── Tool Checker ───────────────────────────────────────────────
check_required_tools() {
  echo ""
  echo "$INFO  Checking required tools from $TOOL_CONFIG..."
  echo "---------------------------------------------"

  mapfile -t tools < <(yq -r '.REQUIRED_TOOLS[].name' "$TOOL_CONFIG")

  for tool in "${tools[@]}"; do
    version=$(yq -r ".REQUIRED_TOOLS[] | select(.name == \"$tool\") | .version" "$TOOL_CONFIG")
    check_tool "$tool" "$version"
  done
}

# ── Module Package Checker ─────────────────────────────────────
check_module_packages() {
  echo ""
  echo "$INFO  Checking module-specific packages from $MODULE_CONFIG..."
  echo "---------------------------------------------"

  if [ ! -f "$MODULE_CONFIG" ]; then
    echo "$FAIL $MODULE_CONFIG not found. Skipping package checks."
    return
  fi

  # Extract global and module-specific packages correctly
  mapfile -t global_packages < <(yq -r '.GLOBAL_PACKAGES[] | select(.NAME) | .NAME' "$MODULE_CONFIG")
  mapfile -t module_packages < <(yq -r '.MODULES[].PACKAGES[]? | select(.NAME) | .NAME' "$MODULE_CONFIG")
  packages=($(printf "%s\n" "${global_packages[@]}" "${module_packages[@]}" | sort -u))

  for pkg in "${packages[@]}"; do
    if [[ -z "$pkg" ]]; then  # Skip empty entries
      continue
    fi
    if ! brew list --formula | grep -q "^$pkg$"; then
      echo "$FAIL Missing package: $pkg"
      suggest_install "$pkg"
      ALL_PRESENT=false
    else
      echo "$SUCCESS Found package: $pkg"
    fi
  done
}


scaffold_all_modules() {
  echo ""
  echo "$INFO  Scaffolding all modules from modules.yaml..."
  echo "---------------------------------------------"
  "$SCRIPT_DIR/scaffold_module.sh"
}

# ── Root CMake Generator ───────────────────────────────────────
update_root_cmake() {
  echo ""
  echo "$INFO  Regenerating root CMakeLists.txt from template..."
  echo "---------------------------------------------"

  local version=$(get_project_metadata "$MODULE_CONFIG" "VERSION")
  local project_name=$(get_project_metadata "$MODULE_CONFIG" "PROJECT")
  local cxx_standard=$(get_project_metadata "$MODULE_CONFIG" "CXX_STANDARD")  # New: Retrieve CXX_STANDARD

  if [ -z "$version" ] || [ -z "$project_name" ] || [ -z "$cxx_standard" ]; then
    echo "$FAIL Missing CMAKE.VERSION, CMAKE.PROJECT, or CXX_STANDARD in $MODULE_CONFIG."
    ALL_PRESENT=false
    return
  fi

  # Filter only modules with TYPE of exe or lib (exclude e.g. react)
  local modules_json=$(get_modules_json "$MODULE_CONFIG" | \
    jq '[.[] | select(.TYPE == "exe" or .TYPE == "lib") | {
      NAME: .NAME,
      HAS_TEST: (.TEST // false)
    }]')

  local template_data=$(jq -n \
    --arg version "$version" \
    --arg project "$project_name" \
    --arg cxx_standard "$cxx_standard" \
    --argjson modules "$modules_json" \
    '{ CMAKE_VERSION: $version, CMAKE_PROJECT: $project, CXX_STANDARD: $cxx_standard, MODULES: $modules }')

  render_template "$template_data" "$(get_template_path root-CMakeLists.txt.mustache)" "$ROOT_CMAKE"

  echo "$SUCCESS Root CMakeLists.txt fully regenerated from template."
}

# ── Final Status Report ────────────────────────────────────────
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

# ── Run Setup ──────────────────────────────────────────────────
print_intro
check_required_tools
check_module_packages
scaffold_all_modules
update_root_cmake
report_final_status
