cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(use-pypt)

set(ROOT_PATH ${PROJECT_SOURCE_DIR}) # 当前项目根目录
set(CMAKE_PREFIX_PATH "/HOME/scz5862/run/pkg/libtorch")
find_package(Torch REQUIRED)
# include_directories(./)

add_executable(example-app example-app.cpp ner.cpp) # 编译所有的源文件
target_link_libraries(example-app "${TORCH_LIBRARIES}")
set_property(TARGET example-app PROPERTY CXX_STANDARD 17)   # torch 14以上


add_library(ner SHARED ner.cpp)
target_link_libraries(ner "${TORCH_LIBRARIES}")