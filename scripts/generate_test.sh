#!/bin/bash
set -e

source "$(dirname "$0")/common.sh"

# Input YAML (step spec)
INPUT_YAML="$1"
MODULE_NAME="$2"
TEST_OUTPUT="cppforge/test/test_${MODULE_NAME}.cpp"
TEMPLATE_NAME="bdd_test_cpp.mustache"

if [[ -z "$INPUT_YAML" || -z "$MODULE_NAME" ]]; then
  echo "$FAIL Usage: $0 <step_yaml> <module_name>"
  exit 1
fi

# Convert YAML step spec to JSON compatible with mustache
json_input=$(yq -o=json "$INPUT_YAML")

# Generate test file
echo "$INFO Rendering test for: $MODULE_NAME"
render_template "$json_input" "$(get_template_path "$TEMPLATE_NAME")" "$TEST_OUTPUT"

echo "$SUCCESS Test file generated at: $TEST_OUTPUT"
