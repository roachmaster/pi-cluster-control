#!/usr/bin/env python3
"""
Forge Module Scaffolder
------------------------
This script generates C++ module scaffolding based on predefined layouts. 
It supports different module types (lib, tool, exe, plugin, test-only), each 
with its own layout and CMakeLists.txt generation using Mustache-style templates.
"""

from py.finalize_module import finalize_module
from py.scaffold_utils import create_module_directory
from py.cli_config_loader import load_cli_parser


def scaffold_module(name: str, module_type: str):
    """Scaffold a new module directory with appropriate layout and build config."""
    module_path = create_module_directory(name)
    return finalize_module(module_path, module_type,name)

def parse_args():
    return load_cli_parser().parse_args()

if __name__ == "__main__":
    args = parse_args()
    scaffold_module(args.name, args.type)