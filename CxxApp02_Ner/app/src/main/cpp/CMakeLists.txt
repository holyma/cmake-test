cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 14)

project("cxxapp01")
include(ExternalProject)

set(BUILD_SUBDIR ${ANDROID_ABI})
set(build_DIR ${CMAKE_SOURCE_DIR}/../../../build)

file(GLOB PYTORCH_INCLUDE_DIRS "${build_DIR}/pytorch_android*.aar/headers")
file(GLOB PYTORCH_LINK_DIRS "${build_DIR}/pytorch_android*.aar/jni/${ANDROID_ABI}")
find_library(PYTORCH_LIBRARY pytorch_jni
        PATHS ${PYTORCH_LINK_DIRS}
        NO_CMAKE_FIND_ROOT_PATH
        )
find_library(FBJNI_LIBRARY fbjni
        PATHS ${PYTORCH_LINK_DIRS}
        NO_CMAKE_FIND_ROOT_PATH
        )
include_directories(
        ${PYTORCH_INCLUDE_DIRS}
        ${PYTORCH_INCLUDE_DIRS}/torch/csrc/api/include)



add_library(ner
        SHARED
        Ner.cpp )
target_link_libraries(ner
        PUBLIC
        ${PYTORCH_LIBRARY}
        ${FBJNI_LIBRARY})

