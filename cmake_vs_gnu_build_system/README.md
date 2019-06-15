# CMAKE vs GNU Build System(Autotools)  
学习`cmake`与`GNU build system (autotools)`使用的示例小项目.  

## 目标
- 了解`cmake`构建的原理  
- 了解`autotools`构建的原理    
- 熟悉`cmake`及`autotools`常用命令、配置、参数的使用
- 小示例项目通过`build.py`脚本可同时支持基于`cmake`的构建以及基于`autotools`的构建  
- 通过`cmake`构建可同时支持Windows(vs工程)、Linux平台(makefile)   
- 通过`autotools`构建可支持Linux平台(Makefile)   

## 原理及优劣势小结  
- `cmake`的最大优势在于跨平台, 支持包括`Windows`、`Linux`、`Mac`等, 不同平台上可生成对应的依赖关系文件(如vs工程文件、xcode工程文件、Linux的Makefile等);而`autotools`仅能支持`Unix-like`(支持GNU的系统), 如`Linux`等;     
- `cmake`与`autotools`本身都并不参与编译过程, 其所做的主要的事情还是支持跨平台的工程配置生成及更新;  
- `cmake`的所有配置均通过`CMakeLists.txt`这一个文件完成, 语法简单清晰, 功能强大. 工具也仅一个`cmake`即可; 而`autotools`则相对复杂许多, 工具链依赖`m4`, 包括`autoconf/automake/autoscan/autoreconf/autoheader/libtool`等, 配置则主要通过`configure.ac`(老的名字为`configure.in`)和`Makefile.am`两个文件完成, 语法相对`cmake`也更复杂.   
- 基于`cmake`强大的跨平台性与简单的配置, 新建项目强烈推荐使用; 而`autotools`由于其厚重的历史短时间也不太可能被完全替代, 尤其是许多底层的开源库/工具, 必然经常遇到.   

## CMAKE 使用上的一些小结  
- 注意点  
  - `CMAKE_CXX_COMPILER/CMAKE_C_COMPILER` 此指定编译器的宏必须在`project()`之前设置, 且若要修改, 必须要重新生成(即不能增量更新此宏参数)  
  - `CMAKE_CXX_FLAGS/CMAKE_CXX_FLAGS_DEBUG/CMAKE_CXX_FLAGS_RELEASE` 这些设置编译参数的宏， 必须在`project()`之后设置, 否则可能不会work. 也可以用`add_compile_options()` or `add_definitions()`来代替     
  - `option()`指定参数默认值, 必须在其对应的`if()`之前, 否则`if()`获取不到对应的值   
  - `option()`选项的值修改，比如从`OFF`改为`ON`, 已生成的内容必须要清理下再重新调用`cmake`生成. 因为`option()`定义的选项的对应值会存在`cmake`的缓存里面, 不清理的话一直会使用缓存中的值.     
  - `BUILD_SHARED_LIBS`参数可选择项目中单独编译的`libs`是否生成动态库(默认都是静态库), 若生成动态库, 在linux都不需要把`.so`去install到系统目录中即可运行, 看来已经做好了链接关系(TODO: 还没明白怎么做的)   
  - 在windows上`cmake`为`MSVC`生成的工程文件, 一份中会同时包含`Debug/Release/RelWithDebugInfo/MinSizeRel`等几个配置. 意味着在windows上不需要根据不同的`CMAKE_BUILD_TYPE`而生成不同的工程文件(`cmake`实际上在生成`MSVC`工程文件时会忽略`CMAKE_BUILD_TYPE`).  

- 杂项  
  - cmake中也有带入版本号给`config.h`的方法, 但个人意见不太好用, 不如像原来那样通过脚本直接获取并生成单独的`version.h`文件  

## 目录文件结构  
- autoclean.sh        # 清理`autotools`生成的临时/编译文件   
- autogen.sh          # 调用`autotools`系列工具生成`configure`脚本及`Makefile`, `config.h`文件  
- _build/  
  - Windows           # 生成 MSVC 工程的目录, Debug/Release等配置在同一份工程中  
  - Release           # linux 上生成 Release 时的目录   
  - Debug             # linux 上生成 Debug 时的目录  
- build.py            # 生成脚本文件, 调用`cmake/autotools/make`  
- cmake_config.h.in   # `cmake` 将根据此文件生成 `cmake_config.h`, 以供源码使用  
- configure.ac        # `autoconf`由此文件生成`configure`脚本  
- CMakeLists.txt      # `cmake` 的关键配置文件  
- main.cc             # 源码入口
- Makefile.am         # `automake`基于此文件生成`Makefile.in`  
- math_lib/           # `power2()` 的实现源码, 将编译成 static/shared lib  
  - CMakeLists.txt    # 子 lib 的 `cmake` 配置文件  
  - math_lib.cc       # 函数实现  
  - math_lib.h        # 头文件  
- README.md           # 说明文件  

### Reference links   
- http://stackoverflow.com/questions/15100351/changing-cmake-cxx-flags-in-project  
- https://cmake.org/Wiki/CMake_Useful_Variables  
- [GNU Autoconf Manual]( https://www.gnu.org/software/autoconf/manual/autoconf.html)  
- [A Good Autotools Tutorial for beginners](http://markuskimius.wikidot.com/programming:tut:autotools)  

## TODO:  
- 与原版本管理系统相结合  
