from pathlib import Path

def write_file(path: Path, content: str):
    """Write text content to a file with error diagnostics."""
    try:
        path.write_text(content)
    except Exception as e:
        snippet = content[:200].replace("\n", "\\n") + ("..." if len(content) > 200 else "")
        print(f"\n🚨 Failed to write file: {path}")
        print(f"📄 Content snippet: {snippet}")
        raise RuntimeError(f"❌ Error writing to file: {path}") from e