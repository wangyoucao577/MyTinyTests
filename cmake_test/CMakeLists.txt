
# CMake 最低版本要求
cmake_minimum_required (VERSION 3.8)

# compile toolchain (should set before `project()`)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -UDEBUG")

# project basic information
project (cmake_test)
set (CMAKE_TEST_VERSION_MAJOR "0")
set (CMAKE_TEST_VERSION_MINOR "1")
set (CMAKE_TEST_VERSION_PATCH "0")


# find source files automatically, then set to var DIR_SRCS
aux_source_directory(. DIR_SRCS)
#aux_source_directory(math_lib DIR_MATH_LIB_SRCS)

####### option for default ###########
option(USE_MY_MATH_LIB "use my math lib" ON)

# 对于这个命令，若默认使用shared lib, cmake连运行时的链接关系都会设置好
# 意味着 .so 被链接过之后, 不需要安装到系统目录即可查找到并运行 
option(BUILD_SHARED_LIBS "build shared libraries" OFF)

####### option for default ##########

# configs for project, should after default value definition in option
configure_file (
    "${PROJECT_SOURCE_DIR}/${CMAKE_CONFIG_FILE}.in"
    "${PROJECT_SOURCE_DIR}/${CMAKE_CONFIG_FILE}"
)

if (USE_MY_MATH_LIB)
    # add subfolder (will refer CMakeLists.txt file in subfolder)
    add_subdirectory(math_lib)
    set (EXTRA_LIBS ${EXTRA_LIBS} math)
endif (USE_MY_MATH_LIB)

# target
add_executable (pow main.cc  ${DIR_SRCS})

# link lib in subfolder
target_link_libraries(pow ${EXTRA_LIBS})
