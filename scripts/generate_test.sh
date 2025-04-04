#!/bin/bash
set -e

# ── Resolve Root Path from common.sh ─────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/common.sh"

# ── Inputs ───────────────────────────────────────────────────
INPUT_YAML="$1"
MODULE_NAME="$2"
TEMPLATE_NAME="bdd_test_cpp.mustache"
TEST_OUTPUT="$ROOT_DIR/cppforge/test/test_${MODULE_NAME}.cpp"

# ── Validation ───────────────────────────────────────────────
if [[ -z "$INPUT_YAML" || -z "$MODULE_NAME" ]]; then
  echo "$FAIL Usage: $0 <step_yaml> <module_name>"
  exit 1
fi

if [[ ! -f "$INPUT_YAML" ]]; then
  echo "$FAIL Input YAML not found: $INPUT_YAML"
  exit 1
fi

# ── Generate Test ────────────────────────────────────────────
json_input=$(yq -o=json "$INPUT_YAML")

echo "$INFO Rendering test for: $MODULE_NAME"
render_template "$json_input" "$(get_template_path "$TEMPLATE_NAME")" "$TEST_OUTPUT"

echo "$SUCCESS Test file generated at: $TEST_OUTPUT"
