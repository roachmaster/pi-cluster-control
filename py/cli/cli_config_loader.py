import argparse
import yaml
from pathlib import Path

CLI_CONFIG_PATH = Path("config/cli_args.yaml")

def load_cli_parser() -> argparse.ArgumentParser:
    with open(CLI_CONFIG_PATH) as f:
        config = yaml.safe_load(f)

    parser = argparse.ArgumentParser(description=config.get("description", ""))
    subparsers = parser.add_subparsers(dest="command", required=True)

    for cmd_name, cmd_info in config.get("subcommands", {}).items():
        subparser = subparsers.add_parser(cmd_name, help=cmd_info.get("help", ""))

        for arg in cmd_info.get("arguments", []):
            name = arg["name"]
            help_text = arg.get("help", "")
            positional = arg.get("positional", False)
            nargs = arg.get("nargs")
            if positional:
                if nargs:
                    subparser.add_argument(name, help=help_text, nargs=nargs)
                else:
                    subparser.add_argument(name, help=help_text)
            else:
                kwargs = {
                    "help": help_text,
                    "default": arg.get("default"),
                    "choices": arg.get("choices"),
                    "action": arg.get("action")
                }
                subparser.add_argument(name, **{k: v for k, v in kwargs.items() if v is not None})

    return parser