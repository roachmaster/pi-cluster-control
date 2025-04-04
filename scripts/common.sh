#!/usr/bin/env bash

# ── Root Project Path ──────────────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

# ── Emojis for consistent UX ───────────────────────────────
SUCCESS="✅"
FAIL="❌"
INFO="🔍"
DONE="🎉"

# ── Mustache Template Renderer ─────────────────────────────
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

# ── Project Metadata Extractor ─────────────────────────────
get_project_metadata() {
  local config_file="$1"
  local key="$2"
  yq -r ".CMAKE.${key}" "$config_file"
}

# ── Load Module List as JSON ───────────────────────────────
get_modules_json() {
  local config="$1"
  yq -o=json ".MODULES" "$config"
}

# ── Safe Path to Template ──────────────────────────────────
get_template_path() {
  local filename="$1"
  echo "$ROOT_DIR/templates/$filename"
}

# ── Suggest Install Command Based on OS ────────────────────
suggest_install() {
  local tool="$1"
  uname_out="$(uname -s)"

  echo "   To install '$tool':"
  case "${uname_out}" in
    Darwin*)
      echo "   ➤ brew install $tool"
      ;;
    Linux*)
      if command -v apt-get >/dev/null; then
        echo "   ➤ sudo apt-get install $tool"
      elif command -v dnf >/dev/null; then
        echo "   ➤ sudo dnf install $tool"
      elif command -v pacman >/dev/null; then
        echo "   ➤ sudo pacman -S $tool"
      else
        echo "   ➤ Please use your distro’s package manager to install '$tool'"
      fi
      ;;
    *)
      echo "   ➤ Unsupported OS. Please install '$tool' manually."
      ;;
  esac
}

# ── Validate Tool Availability and Version ──────────────────
check_tool() {
  local tool="$1"
  local required_version="$2"

  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "$FAIL Missing: $tool"
    suggest_install "$tool"
    ALL_PRESENT=false
    return
  fi

  local current_version
  case "$tool" in
    bash)
      current_version="$BASH_VERSION"
      ;;
    *)
      current_version=$("$tool" --version 2>/dev/null | head -n 1 | grep -oE '[0-9]+\.[0-9]+(\.[0-9]+)?' | head -n 1)
      ;;
  esac

  local required_major="${required_version%%.*}"
  local current_major="${current_version%%.*}"

  if [[ -n "$required_major" && "$current_major" -lt "$required_major" ]]; then
    echo "$FAIL $tool version $required_version or higher is required. Found: $current_version"
    suggest_install "$tool"
    ALL_PRESENT=false
    return
  fi

  echo "$SUCCESS Found: $tool ($current_version)"
}
