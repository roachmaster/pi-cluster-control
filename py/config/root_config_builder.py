from typing import Any


def extract_root_values_from_master(master_config: dict) -> dict[str, Any]:
    """
    Extract a clean, flattened values section for rendering the root-level CMakeLists.txt.
    This includes flattened CMAKE config and MODULES with HAS_TEST detection.
    """
    # Flatten CMAKE
    cmake_section = master_config.get("CMAKE", {})
    flattened_cmake = {f"CMAKE_{k}": v for k, v in cmake_section.items()}

    # Process MODULES and inject HAS_TEST key
    processed_modules = []
    for mod in master_config.get("MODULES", []):
        module_copy = dict(mod)  # Shallow copy
        module_copy["HAS_TEST"] = module_copy.get("TEST", False) is True
        processed_modules.append(module_copy)

    return {
        **flattened_cmake,
        "MODULES": processed_modules
    }