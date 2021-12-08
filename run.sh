#!/bin/bash
#coding=utf-8

# Strict mode
set -euo pipefail

# Enable remote execution
cd "$(dirname "$0")"

./build/project-cells
