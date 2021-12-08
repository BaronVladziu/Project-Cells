#!/bin/bash
#coding=utf-8

# Strict mode
set -euo pipefail

# Enable remote execution
cd "$(dirname "$0")"

rm -rf build
mkdir build
cd build
cmake ..
make
./project-cells
