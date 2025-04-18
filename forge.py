#!/usr/bin/env python3

from py.cli.cli_config_loader import load_cli_parser
from py.cli.cli_command_factory import get_command_executor


def main():
    parser = load_cli_parser()
    args = parser.parse_args()

    executor = get_command_executor(args.command)
    executor()  # 🔥 Run the associated CLI command


if __name__ == "__main__":
    main()
