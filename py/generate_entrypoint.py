from py.config_loader import ENTRYPOINT_TEMPLATE
from py.template_utils import render_template
from write_file import write_file
from pathlib import Path


def generate_entrypoint(module_path: Path, module_name: str, module_type: str):
    """Generate a main entry point file if the type is executable/tool."""
    if module_type == "lib":
        write_file(module_path / "src" / f"{module_name}.cpp", f"// {module_name}.cpp - generated lib\n")
    elif module_type in ("exe", "tool"):
        content = render_template(ENTRYPOINT_TEMPLATE, {"module_name": module_name})
        write_file(module_path / "src" / f"{module_name}_main.cpp", content)