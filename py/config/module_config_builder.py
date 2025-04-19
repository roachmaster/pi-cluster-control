from py.scaffold.structure_utils import create_directory_structure
from py.config.master_config import MasterConfigDTO
from py.template.values_template_expansion import ValuesTemplateExpansion
from py.template.template_utils import render_template_str

import json
from pathlib import Path

# 🔒 Internal module cache
_module_meta_cache = {}

def validate_rendered_outputs(template_dict: dict, module_name: str, values_context: dict):
    """
    Validates the rendered template output paths and prints debug info on failure.
    """
    root_dir = Path.cwd()

    try:
        for key, entry in template_dict.items():
            output = entry.get("output", "")
            if not output:
                raise ValueError(f"🔴 Alas! The blueprint for '{key}' in module '{module_name}' is missing its destination. A grievous oversight!")

            output_path = Path(output)

            if output_path.name == "":
                raise ValueError(f"🛑 Hark! The path for '{key}' in '{module_name}' be but a ghost — empty and void!")

            allowed_roots = ("forge", "py", "config", "templates", "tmp")
            first_part = output_path.parts[0] if output_path.parts else ""

            if first_part not in allowed_roots:
                safe_values = {
                    k: str(v) if isinstance(v, Path) else v
                    for k, v in values_context.items()
                }

                raise ValueError(
                    f"\n⚠️ Hear me, Blacksmith! The path for '{key}' in '{module_name}' — '{output}' — strayeth from the righteous roots!\n"
                    f"    Tread only within: {allowed_roots}\n"
                    f"    Consult the sacred scroll: '{root_dir}/config/templates.yaml' and right this folly!\n"
                    f"    🔎 OUTPUT: {output}\n"
                    f"    🔧 TEMPLATE ENTRY:\n{json.dumps(entry, indent=2)}\n"
                    f"    📦 VALUES CONTEXT:\n{json.dumps(safe_values, indent=2)}\n"
                )

        print(f"✅ Output paths validated for module: {module_name}")

    except Exception as e:
        raise e

def build_module_config(module_name: str, master_config: MasterConfigDTO) -> dict:
    """
    Construct a per-module configuration dictionary including layout, templates, and inheritance.
    Extracts all relevant values into a dedicated 'VALUES' section for clean rendering.
    Enriches the selected module with the correct TEMPLATE block from TEMPLATES.
    """
    global _module_meta_cache

    if not _module_meta_cache:
        for module in master_config.get_modules():
            name = module["NAME"]
            _module_meta_cache[name] = {
                "module_type": module["TYPE"],
                "module_path": name
            }

    if module_name not in _module_meta_cache:
        raise ValueError(f"❌ Module '{module_name}' not found in master config.")

    module_type = _module_meta_cache[module_name]["module_type"]
    module_path = _module_meta_cache[module_name]["module_path"]
    created_dirs = create_directory_structure(module_path, module_type)

    expander = ValuesTemplateExpansion()
    expanded_name = expander.expands_to_dict("module_name", module_name)
    expanded_type = expander.expands_to_dict("module_type", module_type)

    cmake_config = master_config["CMAKE"]
    flattened_cmake = {f"CMAKE_{k}": v for k, v in cmake_config.items()}
    flattened_dirs = {f"DIR_{k}": v for k, v in created_dirs.items()}

    # 🧠 Expand DEPENDS_ON properly
    raw_depends_on = []
    for module in master_config.get_modules():
        if module["NAME"] == module_name:
            raw_depends_on = module.get("DEPENDS_ON", [])
            break

    expanded_depends_on = []
    for dep in raw_depends_on:
        dep_expansion = ValuesTemplateExpansion().expands_to_dict("module_name", dep)
        dep_expansion["module_name"] = dep  # 🔥 Corrected field: `module_name`, not `NAME`
        expanded_depends_on.append(dep_expansion)

    values_section = {
        **expanded_name,
        **expanded_type,
        "module_name": module_name,
        "module_type": module_type,
        "module_path": module_path,
        **flattened_cmake,
        **flattened_dirs,
        "GLOBAL_PACKAGES": master_config["GLOBAL_PACKAGES"],
        "GLOBAL_TEST_PACKAGES": master_config["GLOBAL_TEST_PACKAGES"],
        "DEPENDS_ON": expanded_depends_on,  # ✅ Correct naming and structure
    }

    # Render and inject the correct TEMPLATE block
    templates_block = master_config["TEMPLATES"].get(module_type, {})
    updated_modules = []

    for module_entry in master_config.get_modules():
        if module_entry["NAME"] == module_name:
            module_entry = module_entry.copy()

            rendered_json = render_template_str(json.dumps(templates_block), values_section)
            rendered_template = json.loads(rendered_json)

            validate_rendered_outputs(rendered_template, module_name, values_section)

            module_entry["TEMPLATE"] = rendered_template

        updated_modules.append(module_entry)

    return {
        "VALUES": values_section,
        "MODULE": next(m for m in updated_modules if m["NAME"] == module_name),
    }