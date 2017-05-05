
# CMake 最低版本要求
cmake_minimum_required (VERSION 3.8)

# project
project (cmake_test)

# compile toolchains and flags
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11")

# target
add_executable (pow main.cc math_lib/math_lib.cc)
