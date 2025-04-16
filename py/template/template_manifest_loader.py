from pathlib import Path
import yaml

TEMPLATE_MANIFEST_PATH = Path("config/templates.yaml")


def load_template_manifest(path: Path = TEMPLATE_MANIFEST_PATH) -> dict:
    """
    Load and return the template generation manifest from the templates.yaml file.
    Each entry describes how a generator should behave: what template to use,
    what keys to extract from config, and where to output the rendered result.
    """
    with open(path) as f:
        manifest = yaml.safe_load(f)

    return manifest.get("TEMPLATES", {})