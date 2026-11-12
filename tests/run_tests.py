"""Compile and run selected C++ regression tests without personal puzzle inputs."""

import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile


def main():
    compiler = shlex.split(os.environ.get("CXX", "g++"), posix=os.name != "nt")
    if not compiler or not shutil.which(compiler[0]):
        raise SystemExit("A C++17 compiler is required. Install g++ or set CXX.")

    tests = Path(__file__).resolve().parent
    with tempfile.TemporaryDirectory(prefix="aoc-regression-") as build:
        for source in sorted(tests.glob("*_test.cpp")):
            executable = Path(build) / (source.stem + (".exe" if os.name == "nt" else ""))
            print(f"Compiling {source.name}", flush=True)
            subprocess.run(
                [*compiler, "-std=c++17", "-O2", "-Wall", "-Wextra", str(source), "-o", str(executable)],
                check=True,
                timeout=60,
            )
            subprocess.run([str(executable)], check=True, timeout=30)


if __name__ == "__main__":
    main()
