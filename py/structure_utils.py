from pathlib import Path
import yaml

LAYOUT_YAML_FILE = Path("templates/module_layouts.yaml")

def create_directory_structure(module_path: Path, module_type: str):
    """
    Create standard directory layout for a module type by loading from external YAML.
    """
    with open(LAYOUT_YAML_FILE) as f:
        layouts = yaml.safe_load(f)["layouts"]

    layout = layouts.get(module_type, [])
    for subdir in layout:
        dir_path = module_path / subdir
        dir_path.mkdir(parents=True, exist_ok=True)
        print(f"📁 Created {dir_path.relative_to(module_path)}/")

def load_module_layouts(layout_yaml_path: Path) -> dict:
    """Load module layout definitions from an external YAML file."""
    with open(layout_yaml_path) as f:
        return yaml.safe_load(f)["layouts"]