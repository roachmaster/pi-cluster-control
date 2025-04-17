import json

from py.config.module_config_builder import build_module_config
from py.template.template_engine import dispatch_all_templates_for_module, dispatch_module_specific_templates_for_module


def finalize_module(module_name, master_config: dict) -> bool:
    """
    Finalize the module setup by creating structure and generating files using the shared template engine.
    Accepts a shared master_config and updates it with the module's generation data.
    """
    module_config = build_module_config(module_name, master_config)
    # pretty print module config to screen and then throw exception
    # 🧠 Pretty-print module config for inspection
    print("\n🔍 Final Module Configuration:")
    #print(json.dumps(master_config.raw(), indent=2, default=str))
    print(json.dumps(module_config, indent=2, default=str))


    # Automatically dispatch all templates for the given module type
    dispatch_all_templates_for_module(module_config)
    dispatch_module_specific_templates_for_module(module_name, master_config)
    return True
