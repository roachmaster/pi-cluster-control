from pathlib import Path

def write_file(path: Path, content: str):
    """Write text content to a file."""
    path.write_text(content)
    print(f"📝 Wrote {path}")