cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
project(forest)
set(CMAKE_CXX_STANDARD 20)
set(TARGET "forest")
find_package(Threads REQUIRED)

set(header_files
${CMAKE_CURRENT_SOURCE_DIR}/include/avltree.h
${CMAKE_CURRENT_SOURCE_DIR}/include/bstree.h
${CMAKE_CURRENT_SOURCE_DIR}/include/btree.h
${CMAKE_CURRENT_SOURCE_DIR}/include/rbtree.h)

include_directories("forest")

if(ENABLE_UNIT_TESTS)
    add_subdirectory(gtest)
endif()

add_executable(${TARGET} main.cpp )
target_include_directories(${TARGET} PUBLIC)