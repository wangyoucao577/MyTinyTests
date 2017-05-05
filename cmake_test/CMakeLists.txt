
# CMake 最低版本要求
cmake_minimum_required (VERSION 3.8)

# project
project (cmake_test)

# compile toolchains and flags
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11")


# find files automatically, and set to var DIR_SRCS and DIR_MATH_LIB_SRCS
aux_source_directory(. DIR_SRCS)
#aux_source_directory(math_lib DIR_MATH_LIB_SRCS)

# add subfolder (will refer CMakeLists.txt file in subfolder)
add_subdirectory(math_lib)

# target
add_executable (pow main.cc  ${DIR_SRCS})

# link lib in subfolder
target_link_libraries(pow math)
