from pathlib import Path

import yaml

from py.template_utils import render_template, render_template_str
from py.write_file import write_file

def dispatch_all_python_templates(flat_py_templates: dict):
    for template_key, template_entry in flat_py_templates.items():
        template_path = Path(template_entry["template"])
        values_path = Path(template_entry["values"])

        if not template_path.exists():
            print(f"❌ Template not found: {template_path}")
            continue
        if not values_path.exists():
            print(f"❌ Values file not found: {values_path}")
            continue

        with open(values_path) as f:
            render_context = yaml.safe_load(f)

        source = render_context.get("SOURCE")
        if not source:
            print(f"❌ Missing SOURCE key in: {values_path}")
            continue

        # Build path from key and SOURCE: py.config.master_config_dto → py/config/{{SOURCE}}.py
        parts = template_key.split(".")
        path_prefix = Path(*parts[:-1])  # e.g., py/config
        filename = f"{source}.py"
        output_path = path_prefix / filename
        rendered = render_template(template_path, render_context)
        write_file(output_path, rendered)
        print(f"📝 Wrote {output_path} ({template_key})")

def dispatch_all_templates_for_module(module_config: dict):
    """
    Dispatch all templates defined for the given module_type from master_config["TEMPLATES"].
    Automatically handles all templates declared under that type.
    """
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
