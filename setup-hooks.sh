#!/bin/bash

HOOK_PATH=".git/hooks/pre-commit"
SCRIPT_PATH="bootstrap.sh"

echo "🔧 Installing Git pre-commit hook..."

# Ensure the Git hooks directory exists
if [ ! -d ".git/hooks" ]; then
  echo "Error: .git/hooks directory not found. Are you in the root of a Git repo?"
  exit 1
fi

# Create symbolic link
ln -sf "../../${SCRIPT_PATH}" "$HOOK_PATH"

# Make sure it's executable
chmod +x "$SCRIPT_PATH"

echo "Pre-commit hook installed!"
echo "→ Now every commit will run: ./${SCRIPT_PATH}"
