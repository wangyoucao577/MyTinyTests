# MyTinyTests
学习时写的一些简单的小例子或自动化使用的一些小工具集合, 包含c#, c/c++, python2/3, windows bat, linux bash等各种语言的实现, 平台含Windows, Linux, iOS/mac OSX, Android等. 尝试用最合适的而不是最熟悉的方法解决问题.


# 说明

### [C#] CheckGateway

基于C#的Console, VS2015中实现, 检查本机Gateway设置. 网络初学者经常会出现误设置多个网关导致一些网络异常的情况，此小工具可检查本机Gateway设置是否仅为一条，若为一条则认为设置正确，否则提示设置错误.

### [C] ipv6_to_ipv4

由于`iOS`上架Apple Store必须要支持`IPv6 only`, 故研究了下`ipv4`和`ipv6`兼容的实现方法, 详见:
- https://github.com/wangyoucao577/MyTinyTests/blob/master/ipv6_to_ipv4/ipv6_to_ipv4/README.md

### [C] simple_top  
参考`top`源码实现的简单的`top`, 实现了`system`的详细`cpu`信息刷新，进程和线程的cpu、虚拟内存、实际内存等信息快照的获取. 若需要实现类似`top`的显示所有进程和线程的`cpu`和`memory`占用，则需要将快照进行计算、排序再显示(需要时可实现).  
详见:  
- https://github.com/wangyoucao577/MyTinyTests/blob/master/linux_c_simple_top/README.md  


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

### [C] C语言其他的一些小例子

- c_pointer_transfer.c  
  `C`语言中的指针传递问题. 需注意的是指针本身也是一个普通类型, 取地址传递才能在函数内部修改其内容.

- c_struct_Inheritance.c  
  `C`语言中的继承. 一般认为`C`语言不支持面向对象, 故没有OO语言的继承性. 但事实上完全可以通过`C`语言中清晰的内存布局特性来实现继承. `C`语言中结构体的地址等同于结构体第一个元素的地址, 所以某地址指向的结构体, 若认为其为指向此结构体首元素的结构体的地址, 同样是成立的. 也即可表述为此结构体的基类为其首元素.

- c_union.c  
  `C`语言中union用法的一个小例子.

- char_array_sizeof.c  
  `C`语言中数组传递的一个小例子. 作为函数形参的`char []`等同于`char *`.

- compare_and_swap.c  
  `GCC`提供的一个原子操作的API, 通过汇编级别的代码来保证赋值类操作的原子性，除了此例子中用到的外还有其他一些. 相对于涉及到操作系统系统调用和应用层同步的锁和互斥量，这组api的效率要高很多. 一般来讲用不到, 仅做了解, 在极端情况下可考虑使用.

- endian.c  
  判断本机字节序.

- minimum_int_test.c  
  来自stackoverflow上的一个例子，`int`型最小整数的验证. `gcc -m32 minimum_int_test.c`, `./a.out`可发现此负数已超出了`int`的限制, 故而返回了true. 进行整数大小判断时, 需注意溢出的问题.

- printf_x.c  
  `printf`打印16进制的用法, 包括大小写, `int64_t` 及 `uint64_t`.

- rlimit_test.c  
  获取和设置`linux`系统的软硬限制的接口, `getrlimit/setrlimit`.

- strcasestr_null_input_test.c  
  `strcasestr`传递`NULL`参数时的行为测试.

- showip.c  
  `getaddrinfo`接口的取`domain name`对应的`ip addresss`的功能尝试, 参考自"Beej's Guide to Network Programming"

- rlnumd.c  
  读"Effective Tcp/Ip Programming"时的"技巧17 让`inetd`启动应用程序"中使用`inetd`启动`network services`的方法. 挺有意思的一个用法，简单实验.

- backtrace.c  
  `libc`中提供的可在程序运行时获取当前堆栈信息的方法. 编译时需加上`-rdynamic`选项以导出符号至`.dynsym`符号表, 输出才能正确显示函数名.   
    `gcc -rdynamic backtrace.c`  
    `./a.out`

- capture_icmp.c  
  通过`SOCK_RAW`捕获`ICMP`消息的实验小代码，参考自"Effective Tcp/Ip Programming"的"技巧40 创建和使用捕获`ICMP`消息的工具".  

- c_const.c  
  `C`中的`const`关键字仅描述变量名为`readonly`, 但实际上还是可以通过地址去修改其内容。小例子。  

- c_usual_arithmetic_conversion.c  
  `ANSI C`中的寻常算术转换(usual arithmetic conversion)的例子. `ANSI C`标准中规定, 不同类型的算术运算/比较时，总是向精度更高的类型进行默认转换，所以可能存在signed int转换为unsigned int的情况，符号变化导致结果出错. 此例子源码`gcc -m32`编译运行即可看到。  

- c_sizeof_operator.c  
  `C`中的`sizeof`实际是一个操作符, 而不是函数. 在操作变量时，可以不用加括号，以`sizeof x`的风格, 在操作类型时，则必须加上括号，如`sizeof(int)`.

- c_str_auto_connect.c  
  `C`中的两个相邻字符串常量会忽略中间的空格, 自动连接为一个字符串, 以方便长字符串的表达.

- c_array_pointer.c  
  `C`语言中的数组和指针本质上是不同的, 最主要的表现是取数据时的操作不同. 具体参考《Expert C Programming》第4章.  

### [C++] char_system
  character system相关的一些小实验, 及windows下的MultiBytes字符编码与UTF-8字符编码的转换接口. linux与windows下默认的字符编码一般都是扩展的ANSI, 即所谓的MultiBytes. C++中支持wchar_t的类型定义, 其在linux下实现使用UTF-32即4字节, 在windows下实现使用UTF-16即2字节(windows下所谓的Unicode默认即UTF-16, 而不是UTF-8).
  代码文件保存为UTF-8, 在代码中写入的中文字符串编码方式即为UTF-8, vs中编译后printf输出为乱码, 需转换为MBCS方可正常显示. 而linux下貌似不受此限制, 无论代码文件保存为UTF-8还是GB2312, 都可以直接用printf正确输出.

### [C++] RESTClientSample
  通过HTTP发送JSON格式数据的小例子, 熟悉JsonCpp库和libcurl库的使用.
  工程文件基于VS2015(VC14), 目前仅配置了x64_debug版本.

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

### [Python2/Python3] inquery_my_public_ip
- inquery_my_public_ip.py, inquery_my_public_ip_py3.py  
  获取本机公网IP的小工具. 分别基于`python2`和`python3`实现. 由于功能本身比较简单, 没有太多区别.

- inquery_my_public_ip.exe, inquery_my_public_ip_py3.exe  
  分别对应于`inquery_my_public_ip.py`和`inquery_my_public_ip_py3.py`的在windows上打包后的exe, 便于在没有`Python`环境的PC上的使用.

### [Python3] lambda_map_sample.py
  `lambda`表达式和函数式编程的`map`学习小例子.

### [Python3] serial_power_on_off.py
  通过串口控制继电器上电/断电的小工具, 便于自动开关机测试.

### [Windows_bat] automatic_power_on_off.bat
  自动定时开关机测试的小工具, 使用`serial_power_on_off.py`控制继电器进行实际的上电/断电控制, 在`Windows_bat`中实现定时循环.
