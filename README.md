# MyTinyTests
学习时写的一些简单的小例子或自动化使用的一些小工具集合, 包含c#, c/c++,  JavaScript, python2/3, Lua, windows bat, linux bash等各种语言的实现, 平台含Windows, Linux, iOS/mac OSX, Android等. 尝试用最合适的而不是最熟悉的方法解决问题.


# 说明

### [C/C++] Alogrithms_and_DataStructures   
算法与数据结构的一些实验代码, 来源包括但不限于《算法导论》、hankerrank、leecode, etc.   
- [alogrithms and data structures](./Algorithms_and_DataStructures/)   

### [C#] CheckGateway

基于C#的Console, VS2015中实现, 检查本机Gateway设置. 网络初学者经常会出现误设置多个网关导致一些网络异常的情况，此小工具可检查本机Gateway设置是否仅为一条，若为一条则认为设置正确，否则提示设置错误.

### [C] ipv6_to_ipv4

由于`iOS`上架Apple Store必须要支持`IPv6 only`, 故研究了下`ipv4`和`ipv6`兼容的实现方法, 详见:
- https://github.com/wangyoucao577/MyTinyTests/blob/master/ipv6_to_ipv4/ipv6_to_ipv4/README.md

### [C] simple_top  
参考`top`源码实现的简单的`top`, 实现了`system`的详细`cpu`信息刷新，进程和线程的cpu、虚拟内存、实际内存等信息快照的获取. 若需要实现类似`top`的显示所有进程和线程的`cpu`和`memory`占用，则需要将快照进行计算、排序再显示(需要时可实现).  
详见:  
- https://github.com/wangyoucao577/MyTinyTests/blob/master/linux_c_simple_top/README.md  

### [C] c_interpositioning
读《Expert C Programming》 5.4 警惕Interpositioning问题时做的实验, 可以通过`LD_PRELOAD`替换将要运行的程序的符号.  不失为一个方便的调试/hack方法, 但使用时还是要足够小心.  
详见:  
- https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/Readme.md

### [C] multicast
`multicast client`的一个实验, 程序主要实现的就是基于`UDP`的`multicast`组播推流, 支持指定网卡和设置`TTL`. 代码本身支持`Windows`和`Linux`, 实验主要是在`Windows`下验证了多网卡时该如何设置组播路由. `Linux`下仅使用`gcc`试了下编译代码, 暂未实施具体实验.

### [C] zlog_test  
学习及尝试`zlog`.   
[zlog_test](./zlog_test/README.md)

### [C] TheCProgrammingLanguage

回顾《The C Programming Language》时敲的一些小sample.

- bit_fields.c  
  C语言中按bit定义变量的用法. 多年前该是为了节约内存设计的, 现在应该早已不需要了. 不过由于C语言中没有bool类型, 其实也可以用这个用法自定义1个bit的bool, 赋值在0和1以外则会报warning, 有助于防止误写.

- minprintf.c, va_param_in_macro.c  
  C语言中变长参数 `...` 的用法及其在 `macro` 中的传递方法.

- simple_cat.c  
  `cat` 的一个简单实现. `stdin/out/err` 都是文件描述符, 故可以以文件形式操作. `cat` 的标准行为即读取文件并输出到`stdout`中.

- dcl.c, my_dcl.c  
  两个简单的`C`语法分析的例子, 在VS2015中实现(Linux上实现稍有区别, 未进行改造). `dcl.c`为书上的例子. `my_dcl.c`为参考`dcl.c`的实现进行的全局变量->局部变量的改造, 减少全局变量的使用.

### [C/C++] c_cc_misc
`C/C++`实现的其他的一些小例子的集合, 整理到统一的文件夹中.  
[c_cc_misc](c_cc_misc/README.md)  

### [C/C++] epoll_test   
高性能IO的实验, 包括Linux下`epoll`的使用, 及规划中的windows下的`IOCP`的实验.   
- [epoll_test](epoll_test/README.md)   

### [C++11] learn_intel_tbb
学习 [Intel - Threading Building Blocks (TBB)](https://software.intel.com/en-us/tbb-documentation) 的基本概念和使用.    
- [Learn Intel TBB](./learn_intel_tbb/README.md)    


### [C++] Mars_test
Wechat刚刚开源的`Mars`库, 学习与测试的一些实验代码.   
- [Mars_Test](mars_test/Readme.md)  

### [C++] char_system
  character system相关的一些小实验, 及windows下的MultiBytes字符编码与UTF-8字符编码的转换接口. linux与windows下默认的字符编码一般都是扩展的ANSI, 即所谓的MultiBytes. C++中支持wchar_t的类型定义, 其在linux下实现使用UTF-32即4字节, 在windows下实现使用UTF-16即2字节(windows下所谓的Unicode默认即UTF-16, 而不是UTF-8).
  代码文件保存为UTF-8, 在代码中写入的中文字符串编码方式即为UTF-8, vs中编译后printf输出为乱码, 需转换为MBCS方可正常显示. 而linux下貌似不受此限制, 无论代码文件保存为UTF-8还是GB2312, 都可以直接用printf正确输出.

### [C++] RESTClientSample
  通过HTTP发送JSON格式数据的小例子, 熟悉`JsonCpp`库和`libcurl`库的使用, 同时新增了`RapidJson`的简单用法.
  工程文件基于`VS2015(VC14)``, 目前仅配置了`x64_debug`版本.

### [C++] rtmp_flv   
RTMP接收并分析FLV的sample. 通过librtmp实现从RTMP服务器视音频流拉取, 并自己实现FLV的协议分析(参照FLV的协议标准 "Adobe Flash Video File Format Specification Version 10.1").     
- [rtmp_flv](rtmp_flv/README.md)

### [CMake/Autotools/C++] cmake_vs_gnu_build_system(autotools)     
学习使用`cmake`与`autotools`构建跨平台的编译系统, `cmake`支持直接在`Windows`上生成`Visual Studio`工程文件, 在`Linux`上生成`Makefile`等. `autotools`则广泛支持`Unix-like System`.  
详见:     
- [CMAKE vs GNU Build System (Autotools)](cmake_vs_gnu_build_system/README.md)  

### [Autotools/C++] gnu_build_system_test  
学习使用 The GNU Build System, 即 `autotools`相关工具, 以生成跨平台的编译系统. 工具包括`autoconf/autoheader/automake/autoreconf/aclocal/...`.   
- [GNU Build System Test](gnu_build_system_test/README.md)  

### [C/C++] shm_test     
学习使用共享内存在`Linux`上的使用, `shm`即`shared memroy`. 含`Posix Shared Memory`, `System V Shared Memory`, `Boost Shared Memory`等多种接口/使用方式. 详见:   
- [shm_test](shm_test/README.md)  

### [C++] boost_test   
学习及尝试boost库, 熟悉其behavior及原理.  
- [boost_test](boost_test/README.md)  

### [C++] operator_overloading   
学习下 `C++` 中的运算符重载的一些示例.   

- [operator_overloading](./operator_overloading/README.md)   

### [C/C++/Python2] Try Memory Caching System - Redis vs. Memcached 
熟悉常用的 Memory Caching System [Redis - REmote DIctionary Server](https://redis.io/) 和 [Memcached](https://memcached.org) 的使用, 以及一些基本的区别.    
- [Try Memory Caching System - Redis vs. Memcached](./try_memory_caching_system/)

### [Python2] cmd_args_test.py  
尝试`argparse`库的使用, 居然以前都不知道有这么方便易用的命令行选项解析的工具. 果然还是应该多思考, 觉得不爽的时候`python`里面总归会有让你爽的方法.官网的指南和手册就已经非常好了, 极力推荐.  
- [python2.7 argparse manual](https://docs.python.org/2.7/library/argparse.html)  
- [python2.7 argparse tutorial](https://docs.python.org/2.7/howto/argparse.html)  

### [Python2] cdeclare.py
  参考《Expert C Programming》书中的规则实现的`cdecl`程序, 未按照书中用`C`实现, 而是用更方便的`python`实现了下. 支持较为复杂的函数声明的分析, 未支持包括`struct`, `enum`,`union`等类型. 比上文中《The C Programming Language》中的`cdcl`实现支持更为全面些. 不过对`C`声明的一些细节规则还是不太理解的，再要深入可能需要看标准了.

### [Python2] files_operation.py
  自己实现的一个常用文件操作的接口集合, 包括`svn add/del`, `file copy/compare`, `mkdir`, `scan folder`等常用操作, 易于业务实现.

### [Python2] regex_search.py
  基于`files_operation.py`扩展实现的一个搜索文件夹中指定扩展名的文件进行正则匹配的小工具, 学习正则表达式时实现. 功能类似简单版的`grep`.

### [Python2] copy_modules.py
  基于`files_operation.py`扩展实现的目录中的`.ko`文件拷贝的小工具.

### [Python2] publish.py
  基于`files_operation.py`扩展实现的小工具, 供`Jenkins`调用实现publish功能, 实际执行的任务为从`src_folder`拷贝各个平台的`debug/release`及`.h`内容到`dst_folder`中, 以实现本地编译后的新版本向服务器上`Release`目录中的发布功能.

### [Python2] replace_public_headers.py
  基于`files_operation.py`扩展实现的`.h`文件更新小工具. 设计目标为比较本地文件夹中的`.h`和服务器上指定版本的文件夹中的`.h`, 对应地修改本地文件夹中的`.h`, 并执行必要的`svn add/del`动作, 便于更新本机所使用的sdk版本时头文件的方便的更新.

### [Python2] webspider_qiushibaike_duanzi.py

  学习Python爬虫，参考"静觅 » Python爬虫实战一之爬取糗事百科段子"实现的抓取糗事百科文字段子的小爬虫.

### [Python2] matplotlib_test   
学习`matplotlib`的使用的小例子, 方便的画图及数学计算.   

### [Python2/Python3] inquery_my_public_ip
- inquery_my_public_ip.py, inquery_my_public_ip_py3.py  
  获取本机公网IP的小工具. 分别基于`python2`和`python3`实现. 由于功能本身比较简单, 没有太多区别.

- inquery_my_public_ip.exe, inquery_my_public_ip_py3.exe  
  分别对应于`inquery_my_public_ip.py`和`inquery_my_public_ip_py3.py`的在windows上打包后的exe, 便于在没有`Python`环境的PC上的使用.

### [Python3] lambda_map_sample.py
  `lambda`表达式和函数式编程的`map`学习小例子.

### [Python2/Python3] serial_power_on_off.py
  通过串口控制继电器上电/断电的小工具, 便于自动开关机测试. 此脚本本身功能比较简单, 做了兼容可同时支持`python2`和`python3`解释执行, 以方便使用.

### [JavaScript/Python2] get_info_from_maps
通过各地图提供商(`AMap`, `BaiduMap`, `Googlemap`, etc)提供的`JavaScript API`抓取信息并制定信息并写入文件至`Chrome file system`.   
详见:    
- https://github.com/wangyoucao577/MyTinyTests/blob/master/get_info_from_maps/README.md


### [Windows_bat] automatic_power_on_off.bat
  自动定时开关机测试的小工具, 使用`serial_power_on_off.py`控制继电器进行实际的上电/断电控制, 在`Windows_bat`中实现定时循环.


### [docker] docker_test  
学习docker的原理与使用.   
- [docker_test](./docker_test/README.md)  

### [Mermaid] Try Mermaid
类似`Markdown`设计思路的文本化画图玩法学习下. 又多了一个画`Flowchart`,`Sequence Diagram`,`Gantt Diagram`的利器.      
- [Try Mermaid](./try_mermaid/README.md)

### [Lua] learn_lua
学习`Lua`的基本使用, 以及与`C`的互操作.    
- [learn_lua](./learn_lua/README.md)    


