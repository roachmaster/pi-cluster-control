from py import master_config_loader
from py.structure_utils import create_directory_structure

# 🔒 Internal module cache
_module_meta_cache = {}


def build_module_config(module_name, master_config: dict) -> dict:
    """
    Construct a per-module configuration dictionary including layout, templates, and inheritance.
    Uses a local cache to avoid repeated lookups.
    """
    global _module_meta_cache

    if not _module_meta_cache:
        # Prime the cache by scanning all module definitions
        modules = master_config.get("MODULES", [])
        for module in modules:
            name = module["NAME"]
            _module_meta_cache[name] = {
                "module_type": module["TYPE"],
                "module_path": name  # Default path assumption
            }

    if module_name not in _module_meta_cache:
        raise ValueError(f"Module '{module_name}' not found in master_config")

    module_type = _module_meta_cache[module_name]["module_type"]
    module_path = _module_meta_cache[module_name]["module_path"]

    created_dirs = create_directory_structure(module_path, module_type)

    module_config = {
        "module_name": module_name,
        "module_type": module_type,
        "module_path": module_path,
        "directories": created_dirs,
        "SNAKE_UPPERCASE_MODULE_NAME": module_name.replace("-", "_").upper()
    }

    # Merge in all global values for shared context (non-destructive)
    module_config.update(master_config)
    return module_config


def register_module_config(module_config: dict, master_config: dict):
    """
    Register the module config into the master config under both dict and list forms.
    """
    name = module_config["module_name"]

    if "MODULE_CONFIGS" not in master_config:
        master_config["MODULE_CONFIGS"] = {}

    if "MODULE_CONFIG_LIST" not in master_config:
        master_config["MODULE_CONFIG_LIST"] = []

    master_config["MODULE_CONFIGS"][name] = module_config
    master_config["MODULE_CONFIG_LIST"].append(module_config)
