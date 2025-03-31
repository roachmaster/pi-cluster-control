#!/bin/bash

SUCCESS="✅"
FAIL="❌"
INFO="🔍"
DONE="🎉"

ALL_PRESENT=true
REQUIRED_TOOLS=(cmake make clang++ brew yq jq)
MODULE_CONFIG="modules.yaml"

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

  # Extract all unique package names
  local packages=( $(yq -r ".modules[].packages[]?" "$MODULE_CONFIG" | sort -u | uniq) )



  for pkg in "${packages[@]}"; do
    if ! brew list --formula | grep -q "^$pkg\$"; then
      echo "$FAIL Missing package: $pkg"
      echo "     Install with: brew install $pkg"
      ALL_PRESENT=false
    else
      echo "$SUCCESS Found package: $pkg"
    fi
  done
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
report_final_status
