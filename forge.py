#!/usr/bin/env python3
"""
Forge Module Scaffolder
------------------------
This script generates C++ module scaffolding based on predefined layouts. 
It supports different module types (lib, tool, exe, plugin, test-only), each 
with its own layout and CMakeLists.txt generation using Mustache-style templates.
"""

import argparse
from pathlib import Path
import yaml

from py.structure_utils import create_directory_structure
from py.template_utils import render_template

# === Load Configuration ===
CONFIG_PATH = Path("config/forge_config.yaml")

with open(CONFIG_PATH) as f:
    config = yaml.safe_load(f)

TEMPLATE_DIR = Path(config["template_dir"])
TEMPLATE_FILES = config["template_files"]

# Resolve all paths
LIB_CMAKE_TEMPLATE = TEMPLATE_DIR / TEMPLATE_FILES["lib_cmake_template"]
EXE_CMAKE_TEMPLATE = TEMPLATE_DIR / TEMPLATE_FILES["exe_cmake_template"]
ENTRYPOINT_TEMPLATE = TEMPLATE_DIR / TEMPLATE_FILES["entrypoint_template"]

def write_file(path: Path, content: str):
    """Write text content to a file."""
    path.write_text(content)
    print(f"📝 Wrote {path}")

def generate_cmakelists(module_name: str, module_type: str) -> str:
    """Generate CMakeLists.txt content using mustache template."""
    if module_type == "lib":
        return render_template(LIB_CMAKE_TEMPLATE, {"module_name": module_name})
    else:
        return render_template(EXE_CMAKE_TEMPLATE, {"module_name": module_name})

def generate_entrypoint(module_path: Path, module_name: str, module_type: str):
    """Generate a main entry point file if the type is executable/tool."""
    if module_type == "lib":
        write_file(module_path / "src" / f"{module_name}.cpp", f"// {module_name}.cpp - generated lib\n")
    elif module_type in ("exe", "tool"):
        content = render_template(ENTRYPOINT_TEMPLATE, {"module_name": module_name})
        write_file(module_path / "src" / f"{module_name}_main.cpp", content)

def scaffold_module(name: str, module_type: str):
    """Scaffold a new module directory with appropriate layout and build config."""
    module_path = Path(name)
    if module_path.exists():
        print(f"❌ Module {name} already exists.")
        return

    module_path.mkdir()
    print(f"📦 Created module: {name}")

    create_directory_structure(module_path, module_type)

    cmake_content = generate_cmakelists(name, module_type)
    write_file(module_path / "CMakeLists.txt", cmake_content)

    generate_entrypoint(module_path, name, module_type)

def parse_args():
    """Parse command-line arguments."""
    parser = argparse.ArgumentParser(description="Forge Module Scaffolder")
    parser.add_argument("name", help="Module name (e.g., bdd-runner)")
    parser.add_argument("--type", choices=["lib", "exe", "tool", "plugin", "test-only"], default="lib", help="Module type")
    return parser.parse_args()

if __name__ == "__main__":
    args = parse_args()
    scaffold_module(args.name, args.type)