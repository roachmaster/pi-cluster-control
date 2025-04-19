#!/usr/bin/env python3

from py.cli.cli_config_loader import load_cli_parser
from py.cli.forge_command_executor import execute_command


def main():
    parser = load_cli_parser()
    args = parser.parse_args()
    execute_command(args)


if __name__ == "__main__":
    main()
