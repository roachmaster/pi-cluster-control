#!/bin/bash
set -e

# ── Resolve Root Path from common.sh ─────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/common.sh"

# ── Configurable Constants ───────────────────────────────────
ANTLR_JAR_URL="https://www.antlr.org/download/antlr-4.13.0-complete.jar"
ANTLR_JAR_NAME="antlr-4.13.0-complete.jar"
ANTLR_JAR_PATH="$ROOT_DIR/$ANTLR_JAR_NAME"
ANTLR_LANG="Python3"

GRAMMAR_FILE="$ROOT_DIR/bdd/BDD.g4"
OUTPUT_DIR="$ROOT_DIR/bdd/parser"
INIT_FILE="$OUTPUT_DIR/__init__.py"

# ── Helper Functions ─────────────────────────────────────────
echoStep() { echo -e "\n▶️  $1"; }

requireCommand() {
  if ! command -v "$1" &>/dev/null; then
    echo "❌ Required command not found: $1"
    exit 1
  fi
}

detectPlatform() {
  OS_TYPE="$(uname -s)"
  ARCH_TYPE="$(uname -m)"

  echoStep "🖥️ Detecting platform..."

  case "$OS_TYPE" in
    Linux)
      PLATFORM="linux"
      ;;
    Darwin)
      if [[ "$ARCH_TYPE" == "arm64" ]]; then
        PLATFORM="macos_silicon"
      else
        PLATFORM="macos_intel"
      fi
      ;;
    *)
      echo "❌ Unsupported OS: $OS_TYPE"
      exit 1
      ;;
  esac

  echo "📦 Detected: $PLATFORM"
}

downloadFile() {
  local url="$1" output="$2"
  echoStep "📥 Downloading ANTLR jar from $url..."
  curl -sSL "$url" -o "$output"
}

installDependencies() {
  echoStep "🔧 Installing system and Python dependencies..."

  case "$PLATFORM" in
    linux)
      sudo apt update -y
      sudo apt install -y default-jdk python3 python3-pip curl
      ;;
    macos_*)
      brew install openjdk python3 curl || true
      ;;
  esac

  pip3 install -q antlr4-python3-runtime PyYAML
}

generateParser() {
  echoStep "⚙️ Generating Python parser from $GRAMMAR_FILE..."
  mkdir -p "$OUTPUT_DIR"
  java -jar "$ANTLR_JAR_PATH" -Dlanguage=$ANTLR_LANG -visitor "$GRAMMAR_FILE" -o "$OUTPUT_DIR"
  touch "$INIT_FILE"
  echo "📁 Added __init__.py to make $OUTPUT_DIR a package"
}

setupAlias() {
  local profile="$HOME/.bashrc"
  [[ "$PLATFORM" == macos_* ]] && profile="$HOME/.zshrc"

  echoStep "🔗 Setting up 'antlr4' CLI alias..."
  grep -q "alias antlr4=" "$profile" || echo "alias antlr4='java -jar $ANTLR_JAR_PATH'" >> "$profile"
  source "$profile"
}

# ── Main Entry Point ─────────────────────────────────────────
main() {
  detectPlatform
  requireCommand java
  requireCommand python3
  requireCommand curl

  installDependencies
  downloadFile "$ANTLR_JAR_URL" "$ANTLR_JAR_PATH"
  generateParser
  setupAlias

  echoStep "✅ BDD toolchain is ready. Run:"
  echo "   python3 $ROOT_DIR/bdd/bdd_to_yaml.py path/to/your_file.bdd"
}

main "$@"
