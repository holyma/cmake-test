cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(use-libtorch)

set(CMAKE_PREFIX_PATH "/mnt/f/sublinux/pkg/libtorch-shared-with-deps-1.12.1+cpu/libtorch")
find_package(Torch REQUIRED)

add_executable(example-app example-app.cpp)
target_link_libraries(example-app "${TORCH_LIBRARIES}")
set_property(TARGET example-app PROPERTY CXX_STANDARD 14)


