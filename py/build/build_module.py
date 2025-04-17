#!/usr/bin/env python3
"""
Forge CLI Command — build
--------------------------
Builds the entire Forge system starting from forge/CMakeLists.txt
"""

import os
import subprocess
from pathlib import Path


def build_command():
    def execute():
        run()
    return execute


def run():
    project_root = Path(__file__).resolve().parents[2]     # rootDir/
    cmake_source_dir = project_root / "forge"              # rootDir/forge/
    cmake_build_dir = project_root / "cmake-build-debug"   # CLion-style dir

    print("🔨 Starting Forge build (CLion-compatible)...")
    print(f"📁 CMake Source Dir : {cmake_source_dir}")
    print(f"📦 Build Output Dir : {cmake_build_dir}")

    cmake_build_dir.mkdir(exist_ok=True)

    try:
        subprocess.run(["cmake", str(cmake_source_dir)], cwd=cmake_build_dir, check=True)
        subprocess.run(["cmake", "--build", "."], cwd=cmake_build_dir, check=True)
        print("✅ Forge build complete.")
    except subprocess.CalledProcessError as e:
        print("❌ Forge build failed.")
        print(e)