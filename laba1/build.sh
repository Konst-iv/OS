#!/usr/bin/env bash
set -e                              # остановка при первой ошибке
cd "$(dirname "$0")"

echo "===== [1/3] Updating source files from git ====="
git pull

echo "===== [2/3] Configuration CMake ====="
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

echo "===== [3/3] Build ====="
cmake --build build -- -j"$(nproc)"

echo "===== Done. Running program: ====="
./build/hello