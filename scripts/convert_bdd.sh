#!/bin/bash
set -e

# ── Resolve Root Path from common.sh ─────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/common.sh"

# ── Config Paths (Relative to Root) ──────────────────────────
CONFIG_FILE="$ROOT_DIR/config/grammar.yaml"
GRAMMAR_FILE=""
PYTHON_SCRIPT=""
JSON_SCRIPT=""

# === Load Configuration ===
load_config() {
  echo "🔍 Loading config from $CONFIG_FILE..."
  GRAMMAR_FILE="$ROOT_DIR/$(yq -r '.GRAMMAR_FILE' "$CONFIG_FILE")"
  PYTHON_SCRIPT="$ROOT_DIR/$(yq -r '.VISITOR_SCRIPT' "$CONFIG_FILE")"
  JSON_SCRIPT="$ROOT_DIR/$(yq -r '.YAML_TO_JSON_SCRIPT' "$CONFIG_FILE")"

  if [[ -z "$GRAMMAR_FILE" || -z "$PYTHON_SCRIPT" || -z "$JSON_SCRIPT" ]]; then
    echo "❌ Missing GRAMMAR_FILE, VISITOR_SCRIPT, or YAML_TO_JSON_SCRIPT in $CONFIG_FILE"
    exit 1
  fi
}

# === Validate Environment ===
verify_environment() {
  echo "✅ Verifying environment..."

  for file in "$GRAMMAR_FILE" "$PYTHON_SCRIPT" "$JSON_SCRIPT"; do
    if [[ ! -f "$file" ]]; then
      echo "❌ Required script not found: $file"
      exit 1
    fi
  done

  command -v yq >/dev/null || { echo "❌ 'yq' is required but not installed."; exit 1; }
  command -v python3 >/dev/null || { echo "❌ 'python3' is required but not installed."; exit 1; }
}

# === Convert the BDD File ===
convert_bdd_file() {
  local input_file="$1"
  local base_name="${input_file%.*}"
  local yaml_output="${base_name}.yaml"
  local json_output="${base_name}_steps.json"

  echo "📄 Converting $input_file to YAML..."
  python3 "$PYTHON_SCRIPT" "$input_file"

  echo "🧪 Converting $yaml_output to step JSON..."
  python3 "$JSON_SCRIPT" "$yaml_output"

  echo "✅ YAML saved to: $yaml_output"
}

# === Main Entry Point ===
main() {
  if [[ -z "$1" ]]; then
    echo "Usage: $0 <path/to/file.bdd>"
    exit 1
  fi

  load_config
  verify_environment
  convert_bdd_file "$1"
}

main "$@"
