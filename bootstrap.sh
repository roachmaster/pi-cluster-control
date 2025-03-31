#!/bin/bash

SUCCESS="✅"
FAIL="❌"
INFO="🔍"
DONE="🎉"

ALL_PRESENT=true
REQUIRED_TOOLS=(cmake make clang++ brew yq jq)
MODULE_CONFIG="modules.yaml"
ROOT_CMAKE="CMakeLists.txt"

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

  local packages=(
    $(yq -r ".modules[].packages[]?" "$MODULE_CONFIG" | sort -u | uniq)
  )

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

  local version=$(yq -r ".cmake.version" "$MODULE_CONFIG")
  local project_name=$(yq -r ".cmake.project" "$MODULE_CONFIG")

  if [ -z "$version" ] || [ -z "$project_name" ]; then
    echo "$FAIL Missing cmake.version or cmake.project in $MODULE_CONFIG."
    ALL_PRESENT=false
    return
  fi

  yq -o=json ".modules[]" "$MODULE_CONFIG" | jq -c '.' | while read -r module; do
    local name=$(echo "$module" | jq -r '.name')
    local type=$(echo "$module" | jq -r '.type')
    local has_test=$(echo "$module" | jq -r '.test // false')

    local cmake_file="$name/CMakeLists.txt"
    local cmake_template=""

    if [ "$type" == "lib" ]; then
      cmake_template="templates/CMakeLists-lib.mustache"
    else
      cmake_template="templates/CMakeLists.txt.mustache"
    fi

    if [ -f "$cmake_file" ]; then
      rm "$cmake_file"
    fi

    sed -e "s/{{MODULE_NAME}}/$name/g" \
        -e "s/{{CMAKE_VERSION}}/$version/g" \
        -e "s/{{CMAKE_PROJECT}}/$project_name/g" \
        "$cmake_template" > "$cmake_file"

    echo "$SUCCESS Regenerated $cmake_file"

    if [ "$has_test" == "true" ]; then
      local test_dir="$name/test"
      local test_cmake="$test_dir/CMakeLists.txt"
      local test_template="templates/test-CMakeLists.txt.mustache"

      mkdir -p "$test_dir"

      if [ -f "$test_cmake" ]; then
        rm "$test_cmake"
      fi

      sed -e "s/{{MODULE_NAME}}/$name/g" \
          -e "s/{{CMAKE_VERSION}}/$version/g" \
          -e "s/{{CMAKE_PROJECT}}/$project_name/g" \
          "$test_template" > "$test_cmake"

      echo "$SUCCESS Regenerated $test_cmake"
    fi
  done
}

inject_cmake_header() {
  echo ""
  echo "$INFO  Replacing root CMakeLists.txt header..."
  echo "---------------------------------------------"

  local version=$(yq -r ".cmake.version" "$MODULE_CONFIG")
  local project_name=$(yq -r ".cmake.project" "$MODULE_CONFIG")

  if [ -z "$version" ] || [ -z "$project_name" ]; then
    echo "$FAIL Missing cmake.version or cmake.project in $MODULE_CONFIG."
    ALL_PRESENT=false
    return
  fi

  local rest_of_file=$(grep -v "cmake_minimum_required" "$ROOT_CMAKE" | grep -v "project(")

  {
    echo "cmake_minimum_required(VERSION $version)"
    echo "project($project_name)"
    echo ""
    echo "$rest_of_file"
  } > "$ROOT_CMAKE"

  echo "$SUCCESS Root CMakeLists.txt header forcibly updated."
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
inject_cmake_header
report_final_status
