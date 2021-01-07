
cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME "monster")
project (${PROJECT_NAME})

if (UNIX)
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -std=c++11") # also coult replace with `add_compile_options(-std=c++11)`
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -UDEBUG")
endif(UNIX)


# check whether flatbuffers available
if (NOT DEFINED FLATBUFFERS_SRC_DIR)
message(FATAL_ERROR " FLATBUFFERS_SRC_DIR is mandatory!")
endif()

# Add FlatBuffers directly to our build. This defines the `flatbuffers` target.
add_subdirectory(${FLATBUFFERS_SRC_DIR}
                 ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build
                 EXCLUDE_FROM_ALL)

#aux_source_directory(. DIR_SRCS)

# target
set(BUILD_BINARY_NAME "build_${PROJECT_NAME}")
set(READ_BINARY_NAME "read_${PROJECT_NAME}")
add_executable (${BUILD_BINARY_NAME} build_monster.cpp)
add_executable (${READ_BINARY_NAME} read_monster.cpp)

# Now simply link against flatbuffers as needed to your already declared target.
# The flatbuffers target carry header search path automatically if CMake > 2.8.11.
target_link_libraries(${BUILD_BINARY_NAME} PRIVATE flatbuffers)
target_link_libraries(${READ_BINARY_NAME} PRIVATE flatbuffers)
