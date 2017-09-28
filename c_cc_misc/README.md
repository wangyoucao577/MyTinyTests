# [C/C++] c_cc_misc
`c/c++`的一些小sample的集合.   

# 说明

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

- determin_binary_32_64bit.c  
  通过`sizeof(void*)`即指针长度来判断当前的binary时`32-bit`or`64bit`编译. 其实一般情况下更多是通过宏来编译时判断, 而这个方法可以在运行时判断, 暂时没有遇到不成立的情况.  


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

- c_array_pointer.c, c_array_pointer_2.c  
  `C`语言中的数组和指针本质上是不同的, 最主要的表现是取数据时的操作不同. 具体参考《Expert C Programming》第4章和第9章.  

- c_multi_array.c  
  `C`语言中多维数组的一个实验, 理解指向其中一维的指针及其运算. 来自《Expert C Programming》 9.6多维数组.

- c_longjmp.c  
  `C`语言中的`longjmp/setjmp`, 可支持调到不同文件的不同函数. 主要用途为错误恢复, 约等于`C++`中的异常.  

- c_segmentationfault.c  
  `C`语言中`segmentation fault`的一种典型场景, 即空指针访问. 做这个简单的实验代码的来源是要尝试`segmentation fault`时是否会生成`coredump`。 对应在`linux`系统上先配置`ulimit -c unlimited`, 然后选择性配置`core_pattern`即`coredump`文件的生成路径, 代码再加上`-g`编译, 则总是可以生成`coredump`文件。  

- c_getchar_sttyraw.c, c_getchar_curses.c  
  `Windows`上原生支持单字符获取, 但`Unix`系系统上一般都需要按回车后整行供程序获取. 这两个小例子实验了下`Linux`上单字符获取的方法(来源《Expert C Programming》 8.6节), 其中`c_getchar_sttyraw.c`是通过`stty`程序改变`terminal`属性的方法, `c_getchar_curses.c`则是基于`libcurses`库实现, 链接时应加上`-lcurses`. (此功能很少的可能性用到, 故未深究其原理. 有需要时再研究.)

- c_determin_sign.c  
  `C`语言判断变量/值/类型是有符号还是无符号类型的实验, 来自《Expert C Programming》. 综合书上和网上的一些提示, 给出的三种方法. 其中方法1和方法2都有其固有的缺陷, 主要是不能支持`char/unsigned char/short/unsigned short`这几种低于4字节的类型, 因为`C`的表达式默认类型提升. 方法三目前基本比较完美, 原理也简单. (实验环境:`CentOS 7 64bit, GCC-4.8.5`)   


### [C++] C++的一些小例子
- cc_polymorphism.cc   
  `C++`多态的一个小实验.
	- 基类和子类定义同名方法, 若基类忘了加`virtual`，则是overload, 不会有多态的特性;  
	- 基类和子类定义同名方法, 基类加上virtual, 则是override(`C++11`可显式加上`override`关键字), 具备多态特性(即运行时绑定: 基类指针指向派生类对象, 相当于绑定到派生类的方法);   
	- 基类的析构函数总是应加上`virtual`, 以使其具备多态特性(`delete`时总是能够调用到派生类的析构函数);  
	- 关于基类与派生类的构造/析构函数调用顺序  
		- 构造时, 总是先调用到基类的构造函数, 再调用到派生类的构造函数  
		- 析构时, 总是先调用到派生类的析构函数, 再调用到基类的析构函数  

- cc_const_reference_member.cc  
	`C++`类中有`const`或`reference`成员, 且并没有显式定义拷贝构造函数和拷贝赋值运算符, 是否可以正常使用它的拷贝构造函数和拷贝赋值运算符呢? 答案居然是都可以..  
