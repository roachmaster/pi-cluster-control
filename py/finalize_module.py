from py.module_config_builder import build_module_config
from py.template_engine import dispatch_all_templates_for_module


def finalize_module(module_name, master_config: dict) -> bool:
    """
    Finalize the module setup by creating structure and generating files using the shared template engine.
    Accepts a shared master_config and updates it with the module's generation data.
    """
    module_config = build_module_config(module_name, master_config)
    # Automatically dispatch all templates for the given module type
    dispatch_all_templates_for_module(module_config)

    return True
