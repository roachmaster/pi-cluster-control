from py.cli.cli_command_factory import get_command_executor
from py.cli.forge_logger import ForgeLogger


def execute_command(args):
    if args.command == "multi":
        total = len(args.commands)
        for idx, cmd in enumerate(args.commands, 1):
            ForgeLogger.warning(f"\n➡️  [{idx}/{total}] Running: {cmd}")
            executor = get_command_executor(cmd)
            executor()
        ForgeLogger.success("\n✅ All commands finished successfully!")
    else:
        ForgeLogger.warning(f"\n➡️  Running command: {args.command}")
        executor = get_command_executor(args.command)
        executor()
        ForgeLogger.success("\n✅ Command finished successfully!")
