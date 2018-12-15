
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
set(CMAKE_GENERATOR "Visual Studio 15 2017 Win64")
message("Expect to use: " ${CMAKE_GENERATOR})
endif(WIN32)

# project basic information
project (test_shared_ptr)

# compile options, should set after `project()`, otherwise it won't work
if (NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Release")
endif()
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# compile options, should set after `project()`, otherwise it won't work
if (UNIX)
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -std=c++11") # also coult replace with `add_compile_options(-std=c++11)`
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -UDEBUG")
endif(UNIX)
if (WIN32)
add_compile_options("/MP")  #multi-processor compile
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D \"DEBUG\" /D \"_DEBUG=1\"")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endif(WIN32)
message("CMAKE_CXX_FLAGS " is ${CMAKE_CXX_FLAGS})
message("CMAKE_CXX_FLAGS_DEBUG " is ${CMAKE_CXX_FLAGS_DEBUG})
message("CMAKE_CXX_FLAGS_RELEASE " is ${CMAKE_CXX_FLAGS_RELEASE})

# include/link directories
find_package(Boost)

# find source files automatically, then set to var DIR_SRCS
aux_source_directory(src DIR_SRCS)

# target
set(TEST_STD_SHARED_PTR_TARGET test_std_shared_ptr)
add_executable (${TEST_STD_SHARED_PTR_TARGET} ${DIR_SRCS})

if (Boost_FOUND)
set(TEST_BOOST_SHARED_PTR_TARGET test_boost_shared_ptr)
add_executable (${TEST_BOOST_SHARED_PTR_TARGET} ${DIR_SRCS})
#add_definitions(-DUSE_BOOST_SHARED_PTR)
set_target_properties(${TEST_BOOST_SHARED_PTR_TARGET} PROPERTIES COMPILE_DEFINITIONS "USE_BOOST_SHARED_PTR")
endif()

# link lib

