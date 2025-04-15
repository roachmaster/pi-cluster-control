from py.structure_utils import create_directory_structure
from py.config.master_config import MasterConfigDTO

# 🔒 Internal module cache
_module_meta_cache = {}


def build_module_config(module_name: str, master_config: MasterConfigDTO) -> dict:
    """
    Construct a per-module configuration dictionary including layout, templates, and inheritance.
    Uses a local cache to avoid repeated lookups. Relies on MasterConfigDTO for accessors.
    """
    global _module_meta_cache

    if not _module_meta_cache:
        # Prime the cache using all defined modules from the DTO
        for module in master_config.get_modules():
            name = module["NAME"]
            _module_meta_cache[name] = {
                "module_type": module["TYPE"],
                "module_path": name  # Default path assumption
            }

    if module_name not in _module_meta_cache:
        raise ValueError(f"❌ Module '{module_name}' not found in master config.")

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

    # Merge all global values from the master config into the local module_config
    module_config.update(master_config.raw())

    return module_config


def register_module_config(module_config: dict, master_config: MasterConfigDTO):
    """
    Register the module config into the master config under both dict and list forms.
    """
    name = module_config["module_name"]
    master_config.set_module_configs_entry(name, module_config)
    master_config.add_module_config_list(module_config)