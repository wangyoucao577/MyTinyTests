# CMake 最低版本要求
cmake_minimum_required (VERSION 3.8)

# compile toolchain (should set before `project()`)
if (UNIX)
message("UNIX-like OS")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")
endif(UNIX)
if (WIN32)
message("Windows")
set(CMAKE_GENERATOR "Visual Studio 14 2015 Win64")
message("Expect to use: " ${CMAKE_GENERATOR})
endif(WIN32)

# project basic information
project (mytest_proto2)

# compile options, should set after `project()`, otherwise it won't work
if (UNIX)
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -std=c++11") # also coult replace with `add_compile_options(-std=c++11)`
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -UDEBUG")
endif(UNIX)
if (WIN32)
add_compile_options("/MP")  #multi-processor compile
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D \"DEBUG\"")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endif(WIN32)
message("CMAKE_CXX_FLAGS " is ${CMAKE_CXX_FLAGS})
message("CMAKE_CXX_FLAGS_DEBUG " is ${CMAKE_CXX_FLAGS_DEBUG})
message("CMAKE_CXX_FLAGS_RELEASE " is ${CMAKE_CXX_FLAGS_RELEASE})


# find source files automatically, then set to var DIR_SRCS
#aux_source_directory(. DIR_SRCS)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PROTOBUF REQUIRED protobuf)
include_directories(${PROTOBUF_INCLUDE_DIRS})
link_directories(${PROTOBUF_LIBRARY_DIRS})

# target
add_executable (write_main write_main.cc addressbook.pb.cc)
add_executable (read_main read_main.cc addressbook.pb.cc)

target_link_libraries(write_main ${PROTOBUF_LIBRARIES})
target_link_libraries(read_main ${PROTOBUF_LIBRARIES})

