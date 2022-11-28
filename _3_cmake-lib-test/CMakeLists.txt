cmake_minimum_required(VERSION 2.8)

project(cmake-lib-test)

add_executable(main main.cpp)
# add_library(hello STATIC  hello.cpp) # 参数：输出库名 输入cpp文件名
add_library(hello SHARED hello.cpp) # 参数：输出库名 输入cpp文件名
