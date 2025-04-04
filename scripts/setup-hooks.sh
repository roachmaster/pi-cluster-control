#!/bin/bash
set -e

# ── Resolve Root Path from common.sh ─────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/common.sh"

HOOK_PATH="${ROOT_DIR}/.git/hooks/pre-commit"
BOOTSTRAP_PATH="scripts/bootstrap.sh"
COMMON_PATH="scripts/common.sh"
SCRIPT_PATH="${ROOT_DIR}/${BOOTSTRAP_PATH}"
COMMON_SCRIPT_PATH="${ROOT_DIR}/${COMMON_PATH}"
MODULE_CONFIG="${ROOT_DIR}/modules.yaml"

echo ""
echo "🔧 Installing Git pre-commit hook..."
echo "→ ROOT_DIR: $ROOT_DIR"
echo "→ HOOK_PATH: $HOOK_PATH"
echo "→ SCRIPT_PATH (bootstrap): $SCRIPT_PATH"
echo "→ COMMON_SCRIPT_PATH: $COMMON_SCRIPT_PATH"

# ── Checks ───────────────────────────────────────────────────

if [ ! -f "$SCRIPT_PATH" ]; then
  echo "❌ Cannot find $SCRIPT_PATH. Make sure it exists in the scripts/ directory."
  exit 1
fi

if [ ! -f "$COMMON_SCRIPT_PATH" ]; then
  echo "❌ Cannot find $COMMON_SCRIPT_PATH. Required by the hook."
  exit 1
fi

if [ ! -f "$MODULE_CONFIG" ]; then
  echo "⚠️  Warning: $MODULE_CONFIG not found. bootstrap.sh may fail until this is created."
fi

if [ ! -d "${ROOT_DIR}/.git/hooks" ]; then
  echo "❌ .git/hooks directory not found. Are you inside a Git repo?"
  exit 1
fi

echo "✅ .git/hooks directory found"

# Prevent dangerous paths
if [[ "$HOOK_PATH" == *scripts* ]]; then
  echo "❌ ERROR: Hook path is resolving to a script. Something is misconfigured!"
  exit 1
fi

# ── Create the Hook ───────────────────────────────────────────
echo "🛠 Writing pre-commit hook to $HOOK_PATH"
cat > "$HOOK_PATH" <<EOF
#!/bin/bash
# Git pre-commit hook

ROOT_DIR="\$(cd "\$(dirname "\$0")/../.." && pwd)"
exec "\$ROOT_DIR/${BOOTSTRAP_PATH}"
EOF

chmod +x "$HOOK_PATH"

echo "✅ Pre-commit hook installed!"
echo "→ Every commit will now trigger: ./${BOOTSTRAP_PATH}"
