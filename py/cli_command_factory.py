import importlib
import yaml
from pathlib import Path

CLI_CONFIG_PATH = Path("config/cli_args.yaml")


def get_command_executor(command_name: str):
    # Load the subcommands from the CLI config
    with open(CLI_CONFIG_PATH) as f:
        config = yaml.safe_load(f)

    subcommands = config.get("subcommands", {})
    if command_name not in subcommands:
        raise ValueError(f"❌ Unknown command: {command_name}")

    # Convention: each subcommand maps to a module named py.{command}_module
    module_name = f"py.{command_name}_module"
    function_name = f"{command_name}_command"

    try:
        module = importlib.import_module(module_name)
        command_fn_factory = getattr(module, function_name)
        return command_fn_factory()
    except (ImportError, AttributeError) as e:
        raise RuntimeError(f"⚠️ Could not load command '{command_name}': {e}")