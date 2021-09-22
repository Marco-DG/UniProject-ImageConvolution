cmake_minimum_required(VERSION 3.5)
project(elaborato_programmazione)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -pthread")

add_subdirectory(test)

set(SOURCE_FILES
        dglib/image.h
        dglib/kernel.h
        dglib/ppm.h
)

add_executable(elaborato_programmazione main.cpp)

add_library(dglib_core ${SOURCE_FILES})

set_target_properties(dglib_core PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(elaborato_programmazione dglib_core)