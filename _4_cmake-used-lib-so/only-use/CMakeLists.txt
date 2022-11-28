cmake_minimum_required(VERSION 3.10)

project(only-use)

# 1.添加自己的库文件+头文件
# 增加头文件
include_directories(include
    "/root/git/tmp/used-lib-so/only-use/hello/include"
)
# 增加库文件
file(GLOB HELLO_LIB "/root/git/tmp/used-lib-so/only-use/hello/lib/*.so")

# 2.生成库 可执行文件
# add_library(hello SHARED libHello.cpp)

add_executable(useLibMain useLibMain.cpp)
target_link_libraries(useLibMain ${HELLO_LIB}) # 参数：文件 依赖的库
