from pathlib import Path
import yaml

LAYOUT_YAML_FILE = Path("config/module_layouts.yaml")

# 🔒 Module-level cache for loaded layouts
_layout_cache: dict | None = None


def get_layout_for_type(module_type: str, layout_yaml_path: Path = LAYOUT_YAML_FILE) -> list[str]:
    """Retrieve the directory layout for the given module type from the YAML config."""
    global _layout_cache
    if _layout_cache is None:
        with open(layout_yaml_path) as f:
            _layout_cache = yaml.safe_load(f).get("layouts", {})

    return _layout_cache.get(module_type, [])


def resolve_module_directories(module_path: Path, layout: list[str]) -> list[Path]:
    """Combine the module root with layout subdirectories to get full paths."""
    return [module_path / subdir for subdir in layout]


def create_directories(dirs: list[Path]) -> dict[str, Path]:
    """
    Create all directories under the 'forge/' root, skipping those that already exist.
    Returns a dict of layout name → created Path.
    """
    created = {}
    for dir_path in dirs:
        full_path = Path("forge") / dir_path
        full_path.mkdir(parents=True, exist_ok=True)
        layout_name = dir_path.name
        created[layout_name] = full_path
        print(f"📁 Created forge/{full_path.relative_to(Path('forge'))}/")
    return created


def create_directory_structure(module_path: Path, module_type: str) -> dict[str, Path]:
    """
    Create standard directory layout for a module type by loading from external YAML.
    Returns a dict of layout subdir names to their full paths.
    """
    layout = get_layout_for_type(module_type)

    directories = resolve_module_directories(Path(module_path), layout)
    return create_directories(directories)