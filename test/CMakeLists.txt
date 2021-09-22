cmake_minimum_required(VERSION 3.5)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES
        run_all_test.cpp
        test_image.cpp
        test_ppm.cpp
)

add_executable(dglib_test ${SOURCE_FILES})

target_link_libraries(dglib_test ${GTEST_BOTH_LIBRARIES} dglib_core)
