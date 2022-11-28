cmake_minimum_required(VERSION 3.0.0)
project(example-app VERSION 0.1.0)

# torch
set(ROOT_PATH ${PROJECT_SOURCE_DIR}) # 当前项目根目录
set(CMAKE_PREFIX_PATH "/HOME/scz5862/run/pkg/libtorch")
find_package(Torch REQUIRED)

# 1.添加自己的库文件+头文件
# 增加头文件
# include_directories(include "/HOME/scz5862/run/libtorch/cmake-pypt-so/include")
include_directories(include "include")
# 增加库文件
file(GLOB NER_LIB "lib/libner.so")

add_executable(example-app main.cpp)
target_link_libraries(example-app "${NER_LIB}" "${TORCH_LIBRARIES}") 
set_property(TARGET example-app PROPERTY CXX_STANDARD 17)   # torch 14以上

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
