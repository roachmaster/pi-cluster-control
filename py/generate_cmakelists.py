from pathlib import Path

from write_file import write_file
from template_utils import render_template
from config_loader import LIB_CMAKE_TEMPLATE, EXE_CMAKE_TEMPLATE

def generate_cmakelists(module_name: str, module_type: str, module_path):
    """Generate CMakeLists.txt content using the appropriate Mustache template from config."""
    template = LIB_CMAKE_TEMPLATE if module_type == "lib" else EXE_CMAKE_TEMPLATE
    cmake_content = render_template(template, {"module_name": module_name})
    write_file(module_path / "CMakeLists.txt", cmake_content)
