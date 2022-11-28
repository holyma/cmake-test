cmake_minimum_required(VERSION 3.10)

project(used-lib-so)


add_library(hello SHARED libHello.cpp)
add_executable(useLibMain useLibMain.cpp)
target_link_libraries(useLibMain hello) # 参数：文件 依赖的库
