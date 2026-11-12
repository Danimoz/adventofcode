# Advent of Code

My Advent of Code solutions and algorithm experiments in C++, Python and TypeScript. The repository contains work from 2023, 2024 and 2025; it is a collection of independent exercises rather than a complete solution set for every year.

## Start here

- [2025 Day 1](2025/day01/cpp/main.cpp): circular dial arithmetic, including counting zero crossings without simulating every click.
- [2025 Day 2](2025/day02/cpp/main.cpp): repeated-digit ranges, with enumeration and an arithmetic optimization for part one.
- [Shared C++ utilities](2025/common/cpp/utils.hpp): input reading, string splitting, trimming and grid construction.
- [2024 TypeScript](2024/src/typescript): earlier solutions and utilities, including merge sort.
- [2024 Python](2024/src/python): earlier puzzle implementations.

## Run a C++ solution

Use a compiler with C++17 support. Each 2025 program reads `input.txt` from its working directory, so place your own puzzle input beside the program before running it. For example, from the repository root on a Unix-like shell:

```sh
cd 2025/day01/cpp
g++ -std=c++17 -O2 main.cpp -o solution
./solution
```

Older Python and TypeScript files have their own execution assumptions; some still reference machine-specific input paths. They are historical exercises, not a unified command-line application. `2025/algorithms` holds separate algorithm experiments.

## Decisions and tradeoffs

The solutions stay close to their individual puzzles so the algorithm is easy to inspect. Shared C++ file and string helpers remove repeated input plumbing without introducing a framework.

Day 1 counts complete revolutions and then handles remaining dial movement. This avoids work proportional to the number of clicks. Day 2 keeps a direct enumeration alongside its arithmetic version, making the optimization easier to compare with a straightforward implementation. The regression tests exercise both approaches on the same bounded ranges.

## Regression tests and CI

Requirements: Python 3.10+ and `g++` with C++17 support. No Python packages or personal puzzle inputs are needed.

```sh
python tests/run_tests.py
```

Set `CXX` to choose another compatible compiler, for example `CXX=clang++ python tests/run_tests.py`.

The tests cover dial wraparound, exact zero landings and full revolutions; deterministic generated rotations checked against a click-by-click reference simulation; repeated-number examples; and agreement between the direct and optimized Day 2 part-one implementations across decimal boundaries.

GitHub Actions compiles and runs these tests on pushes and pull requests. This suite covers selected 2025 solutions, not every historical puzzle file.

Puzzle descriptions and personal inputs are available from [Advent of Code](https://adventofcode.com/).
