import argparse
import yaml
from pathlib import Path

CLI_CONFIG_PATH = Path("config/cli_args.yaml")


def load_cli_parser() -> argparse.ArgumentParser:
    with open(CLI_CONFIG_PATH) as f:
        config = yaml.safe_load(f)

    parser = argparse.ArgumentParser(description=config.get("description", ""))

    for arg in config["arguments"]:
        name = arg["name"]
        help_text = arg.get("help", "")
        if arg.get("positional", False):
            parser.add_argument(name, help=help_text)
        else:
            kwargs = {
                "help": help_text,
                "default": arg.get("default"),
                "choices": arg.get("choices")
            }
            parser.add_argument(name, **{k: v for k, v in kwargs.items() if v is not None})

    return parser
