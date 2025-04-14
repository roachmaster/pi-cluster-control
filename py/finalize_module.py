from structure_utils import create_directory_structure
from generate_cmakelists import generate_cmakelists
from generate_entrypoint import generate_entrypoint

def finalize_module(module_path, module_type, name):
    """
    Finalize the module setup by creating structure, CMakeLists, and entrypoint files.
    Returns True if the module path is valid and setup completes, False otherwise.
    """
    if module_path is None:
        return False

    create_directory_structure(module_path, module_type)
    generate_cmakelists(name, module_type, module_path)
    generate_entrypoint(module_path, name, module_type)
    return True