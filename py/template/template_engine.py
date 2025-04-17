import pystache
import yaml
from pathlib import Path

from py.template.template_utils import render_template, render_template_str
from py.utils.write_file import write_file


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
    Dispatch all templates defined in module_config["MODULE"]["TEMPLATE"].
    Renders and writes each template using the VALUES context.
    """
    values = module_config.get("VALUES", {})
    module = module_config.get("MODULE", {})
    template_block = module.get("TEMPLATE", {})
    module_type = module.get("TYPE", "unknown")

    if not template_block:
        print(f"⚠️ No TEMPLATE block found for module type: '{module_type}'")
        return

    for template_id, entry in template_block.items():
        try:
            print(f"🧩 Dispatching template '{template_id}' for module '{module['NAME']}'")

            # Get template path and output path
            template_path = Path(entry["template"])
            output_path_str = render_template_str(entry["output"], values)
            output_path = Path(output_path_str)

            # Render with VALUES
            rendered = render_template(template_path, values)
            write_file(output_path, rendered)

            print(f"📝 Wrote {output_path} ({module_type}.{template_id})")
        except Exception as e:
            print(f"❌ Error rendering template '{template_id}' for module '{module['NAME']}': {e}")
            raise


def dispatch_module_specific_templates_for_module(module_name: str, master_config: dict):
    """
    Dispatch module-specific templates defined under TEMPLATES[module_name].
    Each section (headers, impls, etc.) contains multiple templates.
    """
    templates_section = master_config.get("TEMPLATES", {}).get(module_name, {})
    if not templates_section:
        print(f"⚠️ No module-specific templates defined for: {module_name}")
        return

    for section_name, templates_group in templates_section.items():
        print(f"\n📂 Section: {section_name}")
        for template_id, template_info in templates_group.items():
            try:

                template_path = Path(template_info["template"])
                output_template = template_info["output"]
                values_path = Path(template_info["values"])

                with open(values_path) as f:
                    values_data = yaml.safe_load(f)

                rendered_output = render_template_str(output_template, values_data)
                output_path = Path(rendered_output)

                rendered_content = pystache.render(template_path.read_text(), values_data)
                output_path.parent.mkdir(parents=True, exist_ok=True)
                output_path.write_text(rendered_content)

                print(f"🧩 Rendered '{template_id}' to {output_path}")
            except Exception as e:
                print(f"❌ Failed to render template '{template_id}' in section '{section_name}': {e}")
