import importlib
import importlib.util
import yaml
from pathlib import Path
from py.template.template_utils import render_template

CLI_CONFIG_PATH = Path("config/cli_args.yaml")
TEMPLATE_PATH = Path("templates/cli/python_command_module.py.mustache")


def get_command_executor(command_name: str):
    # Load the subcommands from the CLI config
    with open(CLI_CONFIG_PATH) as f:
        config = yaml.safe_load(f)

    subcommands = config.get("subcommands", {})
    if command_name not in subcommands:
        raise ValueError(f"❌ Unknown command: {command_name}")

    # Determine the expected module and function
    module_name = f"py.{command_name}.{command_name}_module"
    function_name = f"{command_name}_command"
    module_path = Path(f"py/{command_name}/{command_name}_module.py")

    try:
        # Try importing the module and returning the command factory
        module = importlib.import_module(module_name)
        command_fn_factory = getattr(module, function_name)
        return command_fn_factory()

    except (ImportError, AttributeError) as e:
        print(f"⚠️ Command '{command_name}' not found. Scaffolding...")

        # Create module directory
        module_path.parent.mkdir(parents=True, exist_ok=True)

        # Ensure it's a valid package
        init_file = module_path.parent / "__init__.py"
        init_file.touch(exist_ok=True)

        # Render and write scaffolded command
        rendered = render_template(TEMPLATE_PATH, {"COMMAND_NAME": command_name})
        with open(module_path, "w") as f:
            f.write(rendered)

        print(f"✅ Scaffolding complete: {module_path}")

        # Dynamically load the new module
        spec = importlib.util.spec_from_file_location(module_name, module_path)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)

        command_fn_factory = getattr(module, function_name)
        return command_fn_factory()