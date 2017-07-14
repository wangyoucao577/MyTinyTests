
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
# NOTE: use `cmake -G "Visual Studio 14 2015"` instead set the `CMAKE_GENERATOR` here
#        copy `rc.exe, rc.dll` into visual studio vc bin folder, then it works
#     https://stackoverflow.com/questions/14372706/visual-studio-cant-build-due-to-rc-exe%22
#set(CMAKE_GENERATOR "Visual Studio 14 2015")
endif(WIN32)
message("CMAKE_GENERATOR: " ${CMAKE_GENERATOR})
message("CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})
message("CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})

# project basic information
project (shm)

# compile options, should set after `project()`, otherwise it won't work
if (UNIX)
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS}  -g -std=c++11") # also coult replace with `add_compile_options(-std=c++11)`
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
aux_source_directory(. DIR_SRCS)
source_group("src" FILES ${DIR_SRCS})

# add headers also into the visual studio project
file(GLOB_RECURSE HEADER_FILES "*.h")
#message(${HEADER_FILES})
source_group("headers" FILES ${HEADER_FILES})


####### option for default ###########
#option(USE_MY_MATH_LIB "use my math lib" ON)

# 对于这个命令，若默认使用shared lib, cmake连运行时的链接关系都会设置好
# 意味着 .so 被链接过之后, 不需要安装到系统目录即可查找到并运行 
#option(BUILD_SHARED_LIBS "build shared libraries" OFF)

####### option for default ##########

# target
add_executable (shm  ${DIR_SRCS} ${HEADER_FILES})

# link lib in subfolder
if (UNIX)
target_link_libraries(shm librt.so)
endif()
