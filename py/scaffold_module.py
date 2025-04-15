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


def scaffold_module(module, master_config: dict) -> bool:
    """
    Scaffold a new module directory with appropriate layout and build config.
    Updates master_config with new metadata about the generated module.
    """

    print("\nScaffolding module: " + module["NAME"] + "," + module["TYPE"])
    module_path = create_module_directory(module["NAME"])
    success = finalize_module(module["NAME"], master_config)

    if success:
        master_config.setdefault("MODULE_OUTPUTS", {})[module["NAME"]] = {
            "module_path": str(module_path),
            "type": module["TYPE"]
        }
        master_config.setdefault("GENERATED_MODULES", []).append(module["NAME"])
    return success
