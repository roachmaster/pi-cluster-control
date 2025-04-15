from pathlib import Path

from py.master_config_loader import persist_master_config
from py.template_utils import render_template, render_template_str
from py.write_file import write_file


def dispatch_all_templates_for_module(module_config: dict):
    """
    Dispatch all templates defined for the given module_type from master_config["TEMPLATES"].
    Automatically handles all templates declared under that type.
    """
    persist_master_config(module_config, "template_engine.json")
    templates_by_type = module_config.get("TEMPLATES", {})
    module_type = module_config.get("module_type")

    type_templates = templates_by_type.get(module_type, {})
    if not type_templates:
        print(f"No templates registered for type: '{module_type}'")
        return

    for template_id, template_entry in type_templates.items():
        print(f"🧩 Dispatching template '{template_id}' for type '{module_type}'")

        template_path = Path(template_entry["template"])
        output_path_str = render_template_str(template_entry["output"], module_config)
        output_path = Path(output_path_str)

        rendered = render_template(template_path, module_config)
        write_file(output_path, rendered)

        print(f"📝 Wrote {output_path} ({module_type}.{template_id})")
