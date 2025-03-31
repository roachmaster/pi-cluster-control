#!/bin/bash

# ── Emojis for consistent UX ─────────────────────────────
SUCCESS="✅"
FAIL="❌"
INFO="🔍"
DONE="🎉"

# ── Mustache Template Renderer ───────────────────────────
# Usage: render_template "$json_input" "$template_path" "$output_path"
render_template() {
  local json_input="$1"
  local template_file="$2"
  local output_file="$3"

  if [[ -z "$json_input" || -z "$template_file" || -z "$output_file" ]]; then
    echo "$FAIL render_template: Missing argument(s)."
    return 1
  fi

  echo "$json_input" | mustache - "$template_file" > "$output_file"
}

# ── Project Metadata Extractor ───────────────────────────
# Usage: get_project_metadata "modules.yaml" "version"
get_project_metadata() {
  local config_file="$1"
  local key="$2"
  yq -r ".cmake.${key}" "$config_file"
}

# ── Load Module List as JSON ─────────────────────────────
# Usage: get_modules_json "modules.yaml"
get_modules_json() {
  local config="$1"
  yq -o=json ".modules" "$config"
}

# ── Safe Path to Template ────────────────────────────────
# Usage: get_template_path "main.cpp.mustache"
get_template_path() {
  local filename="$1"
  echo "$(dirname "$0")/templates/$filename"
}
