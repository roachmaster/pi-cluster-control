import subprocess
from pathlib import Path
from py.cli.forge_logger import ForgeLogger


def test_command():
    def execute():
        run()

    return execute


def run():
    ForgeLogger.warning("🧪 Launching Forge Test Runner...")

    forge_test_executable = Path("cmake-build-debug/bin/forge_test")

    if not forge_test_executable.exists():
        ForgeLogger.error(f"❌ Forge Test executable not found at {forge_test_executable}. Please build first.")
        return

    try:
        result = subprocess.run(
            [str(forge_test_executable)],
            check=False,
            text=True
        )

        if result.returncode == 0:
            ForgeLogger.success("✅ Forge tests passed!")
        else:
            ForgeLogger.error(f"❌ Forge tests failed with exit code {result.returncode}")

    except Exception as e:
        ForgeLogger.error(f"💥 Unexpected error while running tests: {e}")
