# cmake_test
学习`cmake`使用的示例小项目.  

## 目标
- 了解cmake的原理  
- 熟悉cmake常用命令、配置、参数的使用
- 小示例项目通过cmake及`build.py`脚本可同时支持Windows(vs工程)、Linux平台(makefile)  

## 原理及优劣势小结  
- cmake的最大优势在于跨平台, 支持包括Windows、Linux、Mac等, 不同平台上可生成对应的依赖关系文件(vs工程文件、Linux的Makefile等);   
- cmake本身并不参与编译过程, 其所做的主要的事情还是支持跨平台的工程配置生成及更新;  

## 使用上的一些小结  
- 注意点  
  - `CMAKE_CXX_COMPILER/CMAKE_C_COMPILER` 此指定编译器的宏必须在`project()`之前设置, 且若要修改, 必须要重新生成(即不能增量更新此宏参数)  
  - `CMAKE_CXX_FLAGS/CMAKE_CXX_FLAGS_DEBUG/CMAKE_CXX_FLAGS_RELEASE` 这些设置编译参数的宏， 必须在`project()`之后设置, 否则可能不会work. 也可以用`add_compile_options()` or `add_definitions()`来代替     
  - `option()`指定参数默认值, 必须在其对应的`if()`之前, 否则`if()`获取不到对应的值   
  - `BUILD_SHARED_LIBS`参数可选择项目中单独编译的`libs`是否生成动态库(默认都是静态库), 若生成动态库, 在linux都不需要把`.so`去install到系统目录中即可运行, 看来已经做好了链接关系(TODO: 还没明白怎么做的)   
  - 在windows上`cmake`为`MSVC`生成的工程文件, 一份中会同时包含`Debug/Release/RelWithDebugInfo/MinSizeRel`等几个配置. 意味着在windows上不需要根据不同的`CMAKE_BUILD_TYPE`而生成不同的工程文件(`cmake`实际上在生成`MSVC`工程文件时会忽略`CMAKE_BUILD_TYPE`).  

- 杂项  
  - cmake中也有带入版本号给`config.h`的方法, 但个人意见不太好用, 不如像原来那样通过脚本直接获取并生成单独的`version.h`文件  

## 目录文件结构  
- _build/  
  - Windows           # 生成 MSVC 工程的目录, Debug/Release等配置在同一份工程中  
  - Release           # linux 上生成 Release 时的目录   
  - Debug             # linux 上生成 Debug 时的目录  
- build.py            # 生成脚本文件, 调用`cmake/make`  
- cmake_config.h.in   # `cmake` 将根据此文件生成 `cmake_config.h`, 以供源码使用  
- CMakeLists.txt      # `cmake` 的关键配置文件  
- main.cc             # 源码入口  
  - CMakeLists.txt    # 子 lib 的 `cmake` 配置文件  
  - math_lib.cc       # 函数实现  
  - math_lib.h        # 头文件  
- math_lib/           # `power2()` 的实现源码, 将编译成 static/shared lib  
- README.md           # 说明文件  

### Reference links   
- http://stackoverflow.com/questions/15100351/changing-cmake-cxx-flags-in-project  
- https://cmake.org/Wiki/CMake_Useful_Variables  

## TODO:  
- 与原版本管理系统相结合  
