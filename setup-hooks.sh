#!/bin/bash

HOOK_PATH=".git/hooks/pre-commit"
SCRIPT_PATH="bootstrap.sh"
MODULE_CONFIG="modules.yaml"

echo "🔧 Installing Git pre-commit hook..."

# Check files
if [ ! -f "$SCRIPT_PATH" ]; then
  echo "❌ Cannot find $SCRIPT_PATH. Make sure it exists in the repo root."
  exit 1
fi

if [ ! -f "$MODULE_CONFIG" ]; then
  echo "⚠️  Warning: $MODULE_CONFIG not found. bootstrap.sh may fail until this is created."
fi

# Ensure hooks dir exists
if [ ! -d ".git/hooks" ]; then
  echo "❌ .git/hooks directory not found. Are you inside a Git repo?"
  exit 1
fi

# Create symlink and ensure executable
ln -sf "../../$SCRIPT_PATH" "$HOOK_PATH"
chmod +x "$SCRIPT_PATH"

echo "✅ Pre-commit hook installed!"
echo "→ Now every commit will run: ./$SCRIPT_PATH"
