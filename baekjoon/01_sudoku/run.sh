#!/bin/bash
if [ $# -lt 1 ]; then
    echo "Usage: $0 <input file>"
    exit 1
fi

g++-15 main.cpp -o prog
./prog "./input/$1"
rm -rf ./prog
