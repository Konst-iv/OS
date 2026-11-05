
cmake_minimum_required(VERSION 3.10)

project(ProcessRunner VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_executable(process_runner_test
    tests/process_runner_test.cpp
    src/process_runner.cpp
)

target_include_directories(process_runner_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
