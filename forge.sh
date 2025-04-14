#!/bin/bash
set -e

# ── Resolve Root Path from common.sh ─────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/scripts/common.sh"

SCRIPTS_DIR="$ROOT_DIR/scripts"
BDD_TO_YAML_SCRIPT="$SCRIPTS_DIR/convert_bdd.sh"

SCAFFOLD_SCRIPT="$SCRIPTS_DIR/scaffold_module.sh"
BOOTSTRAP_SCRIPT="$SCRIPTS_DIR/bootstrap.sh"
BUILD_DIR="$ROOT_DIR/cmake-build-debug"

# ── Usage Help ───────────────────────────────────────────────
usage() {
  echo "Usage: ./forge.sh <command> [options]"
  echo ""
  echo "Commands:"
  echo "  bootstrap"
  echo "      Run environment bootstrap and validate required tools."
  echo ""
  echo "  scaffold [--only-cmake] [--dry-run]"
  echo "      Generate C++ modules from modules.yaml."
  echo "      --only-cmake   Only generate CMake files (skip sources/tests/features)"
  echo "      --dry-run      Show what would be created without writing files"
  echo ""
  echo "  convert-bdd <file.bdd>"
  echo "      Convert a BDD spec file into YAML using the ANTLR-based visitor."
  echo ""
  echo "  test"
  echo "      Build and run CTest-based project tests"
  exit 1
}



cmd_convert_bdd() {
  local file="$1"
  if [[ -z "$file" ]]; then
    echo "❌ Missing .bdd file path"
    usage
  fi

  # Ensure BDD parser is built before conversion
  echo "🔄 Ensuring BDD toolchain is ready..."
  "$SCRIPTS_DIR/setup_bdd_toolchain.sh"

  "$BDD_TO_YAML_SCRIPT" "$file"
}

cmd_build() {
  echo "🧪 Running build..."
  cmake --build "$BUILD_DIR" --verbose
}

cmd_test() {
  echo "🧪 Running tests..."
  cmake --build "$BUILD_DIR"
  ctest --test-dir "$BUILD_DIR" --output-on-failure --verbose
}

# ── Command Router ───────────────────────────────────────────
main() {
  local cmd="$1"
  shift || true

  case "$cmd" in
    bootstrap)      cmd_bootstrap "$@" ;;
    scaffold)       cmd_scaffold "$@" ;;
    convert-bdd)    cmd_convert_bdd "$@" ;;
    test)           cmd_test "$@" ;;
    build)           cmd_build "$@" ;;
    *)              usage ;;
  esac
}

main "$@"
