cmake_minimum_required(VERSION 3.10)
project(kriging_weng)

#find_package(GLEW REQUIRED)
#message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")

#include_directories(GLEW_INCLUDE_DIR)
include_directories(include)
file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "include/*.h include/data/*.h")

add_executable(kriging_weng ${SRC_DIR_LIST})
#link_directories(xxxx)
#target_link_libraries(kriging_weng XXXX)
