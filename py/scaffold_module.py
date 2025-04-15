#!/usr/bin/env python3
"""
Forge Module Scaffolder
------------------------
This script generates C++ module scaffolding based on predefined layouts. 
It supports different module types (lib, tool, exe, plugin, test-only), each 
with its own layout and CMakeLists.txt generation using Mustache-style templates.
"""

from py.finalize_module import finalize_module
from py.master_config_loader import load_master_config, persist_master_config
from py.scaffold_utils import create_module_directory

def scaffold_command():
    def execute():
        run_scaffold()
    return execute

def run_scaffold():
    master_config = load_master_config()
    modules = master_config.get_modules()

    print(f"🔧 Starting Forge generation for {len(modules)} modules...")

    for module in modules:
        scaffold_per_module(module, master_config)

    print("\n✅ All modules processed.\n")
    persist_master_config(master_config)

def scaffold_per_module(module, master_config) -> bool:
    """
    Scaffold a new module directory with appropriate layout and build config.
    Updates master_config with new metadata about the generated module.
    """
    print(f"\nScaffolding module: {module['NAME']}, {module['TYPE']}")
    module_path = create_module_directory(module["NAME"])
    success = finalize_module(module["NAME"], master_config)

    if success:
        master_config.set_module_outputs_entry(module["NAME"], {
            "module_path": str(module_path),
            "type": module["TYPE"]
        })
        master_config.add_generated_modules(module["NAME"])

    return success