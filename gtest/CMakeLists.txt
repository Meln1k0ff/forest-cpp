# Add threading library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TARGET "forest-test")

# get_target_property(PROJECT_CPP_FILES media-framework SOURCES)
# list(FILTER PROJECT_CPP_FILES EXCLUDE REGEX "main.cpp$")
# message(STATUS CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${TARGET}
    ${PROJECT_CPP_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

# add_subdirectory(utils)#

#include_directories(bsTree)

## Include application root
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../media-framework")

add_test(NAME test_${TARGET} COMMAND ${TARGET})
