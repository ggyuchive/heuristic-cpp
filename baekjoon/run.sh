#!/bin/bash

# Usage check
if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory> <input file>"
    echo "Example: $0 01_sudoku 05.in"
    exit 1
fi

DIR="$1"
IN_FILE="$2"

SRC="./${DIR}/main.cpp"
IN_DIR="./${DIR}/input/${IN_FILE}"
OUT="prog"

# Check source file
if [ ! -f "$SRC" ]; then
    echo "Error: Source file not found → $SRC"
    exit 1
fi

# Check input file
if [ ! -f "$IN_DIR" ]; then
    echo "Error: Input file not found → ${IN_DIR}"
    exit 1
fi

# Compile
echo "🔧 Compiling $SRC ..."
g++-15 -std=c++20 "$SRC" -o "$OUT"
if [ $? -ne 0 ]; then
    echo "❌ Compilation failed!"
    exit 1
fi

# Execute
echo "🚀 Running with input file: ${IN_DIR}"
./"$OUT" "${IN_DIR}"

# Cleanup
rm -f "$OUT"
