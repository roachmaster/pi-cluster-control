from pathlib import Path
import pystache


def render_template(template_path: Path, context: dict) -> str:
    """Render a Mustache template with a given context."""
    return pystache.render(template_path.read_text(), context)


def render_template_str(template_str: str, context: dict) -> str:
    """Render a Mustache template with a given context."""
    return pystache.render(template_str, context)
