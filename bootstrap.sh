#!/bin/bash

# Style
SUCCESS="✅"
FAIL="❌"
INFO="🔍"
DONE="🎉"

ALL_PRESENT=true

macos_get_required_tools() {
  echo "cmake make clang++ brew"
}

macos_check_required_tools() {
  for tool in $(macos_get_required_tools); do
    if ! command -v "$tool" >/dev/null 2>&1; then
      echo "$FAIL Missing: $tool"
      ALL_PRESENT=false
    else
      echo "$SUCCESS Found: $tool"
    fi
  done
}

macos_report_final_status() {
  echo "---------------------------------------------"
  if [ "$ALL_PRESENT" = true ]; then
    echo "$DONE Environment is ready for C++ development on macOS."
    exit 0
  else
    echo "$FAIL Some required tools are missing."
    echo "    Please install them using Homebrew:"
    echo "    /bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
    echo ""
    echo "    Then run:"
    echo "    brew install cmake make"
    echo ""
    exit 1
  fi
}

macos_print_intro() {
  echo ""
  echo "$INFO  Verifying C++ build environment for macOS..."
  echo "---------------------------------------------"
}

macos_check_env() {
  macos_print_intro
  macos_check_required_tools
  macos_report_final_status
}

# ── Entry Point ─────────────────────────────
macos_check_env
