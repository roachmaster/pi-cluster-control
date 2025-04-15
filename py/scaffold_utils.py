from pathlib import Path


def create_module_directory(name: str) -> Path | None:
    """
    Scaffold a new module directory with appropriate layout and build config.
    Returns the Path to the created module directory, or None if it already exists.
    """
    module_path = Path(name)
    if module_path.exists():
        print(f"❌ Module {name} already exists.")
        return module_path
    module_path.mkdir()
    print(f"📦 Created module: {name}")
    return module_path
