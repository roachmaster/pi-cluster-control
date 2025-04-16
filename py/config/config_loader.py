from pathlib import Path
import yaml

CONFIG_PATH = Path("config/forge_config.yaml")

with open(CONFIG_PATH) as f:
    config = yaml.safe_load(f)

TEMPLATE_DIR = Path(config["template_dir"])
TEMPLATE_FILES = config["template_files"]

# Resolve all template paths
LIB_CMAKE_TEMPLATE = TEMPLATE_DIR / TEMPLATE_FILES["lib_cmake_template"]
EXE_CMAKE_TEMPLATE = TEMPLATE_DIR / TEMPLATE_FILES["exe_cmake_template"]
ENTRYPOINT_TEMPLATE = TEMPLATE_DIR / TEMPLATE_FILES["entrypoint_template"]