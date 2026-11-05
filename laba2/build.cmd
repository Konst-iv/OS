
@echo off
setlocal
cd /d "%~dp0"

echo ===== [1/3] Updating source files from git =====
git pull
if %errorlevel% neq 0 (
    echo Error: git pull failed
    exit /b 1
)

echo ===== [2/3] Configuration CMake =====
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
if %errorlevel% neq 0 (
    echo Error configuring CMake
    exit /b 1
)

echo ===== [3/3] Build =====
cmake --build build
if %errorlevel% neq 0 (
    echo Error building
    exit /b 1
)

echo ===== Done. Running program: =====
build\process_runner_test.exe

endlocal
