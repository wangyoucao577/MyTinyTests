
# CMake 最低版本要求
cmake_minimum_required (VERSION 3.8)

# compile toolchain (should set before `project()`)
if (WIN32)
message("Windows")
set(CMAKE_GENERATOR "Visual Studio 14 2015")
endif(WIN32)
message("Expect to use: " ${CMAKE_GENERATOR})
message("Plaform name: " ${CMAKE_GENERATOR_PLATFORM}) # set by `cmake -A `
if (${CMAKE_GENERATOR_PLATFORM} MATCHES "x64")
set(LIB_SUB_FOLDER_NAME "win64")
else()
set(LIB_SUB_FOLDER_NAME "win32")
endif()

# project basic information
project (zlog_test)

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
include_directories(include/winzlog)


####### option for default ###########

# 对于这个命令，若默认使用shared lib, cmake连运行时的链接关系都会设置好
# 意味着 .so 被链接过之后, 不需要安装到系统目录即可查找到并运行 
option(BUILD_SHARED_LIBS "build shared libraries" OFF)

####### option for default ##########


# target
add_executable (zlog_main main.cc)
add_executable(dzlog_main dzlog_main.cc)

# link lib in subfolder
message(${PROJECT_SOURCE_DIR})
target_link_libraries(dzlog_main 
${PROJECT_SOURCE_DIR}/lib/${LIB_SUB_FOLDER_NAME}/zlog.lib
)
target_link_libraries(zlog_main 
${PROJECT_SOURCE_DIR}/lib/${LIB_SUB_FOLDER_NAME}/zlog.lib
)
