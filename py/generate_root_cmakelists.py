from pathlib import Path
from py.template_utils import render_template
from write_file import write_file

ROOT_CMAKE_TEMPLATE = Path("templates/root_cmakelists.mustache")
ROOT_CMAKE_FILE = Path("CMakeLists.txt")  # This must be a Path object


def generate_root_cmakelists(config: dict):
    """Render and write the root CMakeLists.txt from the full module.yaml config."""
    template = ROOT_CMAKE_TEMPLATE
    rendered = render_template(template, config)

    write_file(ROOT_CMAKE_FILE, rendered)
    print(f"📝 Wrote {ROOT_CMAKE_FILE}")
