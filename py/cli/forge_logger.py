# py/cli/forge_logger.py

class ForgeLogger:
    class Color:
        RESET = "\033[0m"
        BLUE = "\033[94m"
        GREEN = "\033[92m"
        YELLOW = "\033[93m"
        RED = "\033[91m"

    @staticmethod
    def print(message: str, color: str = Color.BLUE):
        print(f"{color}{message}{ForgeLogger.Color.RESET}")

    @staticmethod
    def info(message: str):
        ForgeLogger.print(message, ForgeLogger.Color.BLUE)

    @staticmethod
    def success(message: str):
        ForgeLogger.print(message, ForgeLogger.Color.GREEN)

    @staticmethod
    def warning(message: str):
        ForgeLogger.print(message, ForgeLogger.Color.YELLOW)

    @staticmethod
    def error(message: str):
        ForgeLogger.print(message, ForgeLogger.Color.RED)