from pathlib import Path
import json
from py.config.root_config_builder import extract_root_values_from_master
from py.template.template_utils import render_template_str, render_template

from pathlib import Path
import json
from py.config.root_config_builder import extract_root_values_from_master
from py.template.template_utils import render_template_str, render_template


def scaffold_root(master_config: dict):
    """
    Scaffold all templates defined in TEMPLATES.root using the extracted root-level values.
    """
    root_templates = master_config.get("TEMPLATES", {}).get("root", {})
    root_values = extract_root_values_from_master(master_config)
    print("\n📦 Root Template Values:\n" + json.dumps(root_values, indent=2))
    if not root_templates:
        print("⚠️ No root templates found to scaffold.")
        return

    for template_id, entry in root_templates.items():
        template_path_str = entry.get("template")
        output_template_str = entry.get("output")

        if not template_path_str or not output_template_str:
            print(f"⚠️ Skipping root template '{template_id}' due to missing fields.")
            continue

        template_path = Path(template_path_str)
        output_path_str = render_template_str(output_template_str, root_values)
        output_path = Path(output_path_str)

        rendered = render_template(template_path, root_values)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(rendered)

        print(f"📝 Wrote {output_path} (root.{template_id})")
