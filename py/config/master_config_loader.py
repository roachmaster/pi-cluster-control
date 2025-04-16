from pathlib import Path
import yaml
import json
from py.template.template_manifest_loader import load_template_manifest
from py.config.master_config import MasterConfigDTO  # <- Import the DTO

MODULES_YAML_FILE = Path("modules.yaml")
LAYOUT_YAML_FILE = Path("config/module_layouts.yaml")


def load_project_config(path: Path) -> dict:
    with open(path) as f:
        return yaml.safe_load(f)


def load_layout_definitions(path: Path = LAYOUT_YAML_FILE) -> dict:
    with open(path) as f:
        return yaml.safe_load(f).get("layouts", {})


def load_master_config(
        module_file: Path = MODULES_YAML_FILE,
        layout_file: Path = LAYOUT_YAML_FILE
) -> MasterConfigDTO:
    master_config = load_project_config(module_file)
    master_config["TEMPLATES"] = load_template_manifest()
    master_config["LAYOUTS"] = load_layout_definitions(layout_file)
    master_config["GENERATED_MODULES"] = []
    return MasterConfigDTO(master_config)


def persist_master_config(master_config: MasterConfigDTO, filename: str = "scaffold_run.json") -> None:
    tmp_dir = Path("tmp")
    tmp_dir.mkdir(exist_ok=True)

    output_path = tmp_dir / filename
    with open(output_path, "w") as f:
        json.dump(master_config.raw(), f, indent=2, default=str)

    print(f"\n🧠 Master config written to: {output_path}")