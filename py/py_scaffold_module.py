#!/usr/bin/env python3
"""
Forge Python Scaffold Generator
-------------------------------
This script generates Python DTOs and other Python-based files based on declarative templates.
It supports DTO generation from YAML configs using Mustache-style templates.
"""

import json

from py.master_config_loader import load_master_config, persist_master_config
from py.template_engine import dispatch_all_python_templates


def py_scaffold_command():
    def execute():
        run()
    return execute


def flatten_py_templates(templates: dict) -> dict:
    """
    Flatten the nested TEMPLATES.py dictionary into TEMPLATES.py.config.key style.
    """
    flat_templates = {}
    py_section = templates.get("py", {})
    for category, entries in py_section.items():
        for name, template_data in entries.items():
            full_key = f"py.{category}.{name}"
            flat_templates[full_key] = template_data
    return {"TEMPLATES": flat_templates}


def run():
    master_config = load_master_config()
    templates = master_config.get_templates()  # Uses DTO method
    flattened = flatten_py_templates(templates)

    print("📦 Flattened Python Templates:")
    print(json.dumps(flattened, indent=2))

    # 🔥 Dispatch generation
    dispatch_all_python_templates(flattened["TEMPLATES"])

    persist_master_config(master_config)