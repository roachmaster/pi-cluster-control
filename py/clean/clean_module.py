#!/usr/bin/env python3
"""
Forge CLI Command — clean
------------------------------------
Cleans all CLion build artifacts (cmake-build-*) from the project root.
"""

import shutil
from pathlib import Path

def clean_command():
    def execute():
        run()
    return execute

def run():
    print("🧹 Starting Forge clean...")

    PROJECT_ROOT = Path(".")
    folders_to_clean = [p for p in PROJECT_ROOT.rglob("cmake-build-*") if p.is_dir()]
    if not folders_to_clean:
        print("🧹 Nothing to clean. No build folders found.")
        return

    for folder in folders_to_clean:
        print(f"🧹 Removing folder: {folder}")
        shutil.rmtree(folder)

    print("✅ Forge project cleaned.")