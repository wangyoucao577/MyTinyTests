# [C++11] cc11
C++11新特性尝试的一些代码及工程集合, 测试代码主要来源于《Understanding C++11 -- Analysis and Application of New Features》.  

## 阅读与运行
- `Windows`: 可通过`cc_test.sln`(`VS2015`)打开所有的工程及代码, 选择某个工程进行编译及运行即可.   
- `Linux`: `g++ [-m32] -std=c++11 -I../src_comm/ xxx.cc` 编译, 然后运行即可  
- `MacOSX` : `clang++ [-m32] -std=c++11 -I../src_comm/ xxx.cc` 命令行编译, 然后`./a.out`运行即可(未创建XCode工程) 

## 实验平台
- `Windows`: `Win10 64bit`, `Visual Studio 2015 Update 3`  
- `Linux`: `CentOS7 64bit`, `Kernel 3.10.0-229.el7.x86_64`, `gcc 4.8.5 20150623`  
- `MacOSX`: `MacBook Air (13-inch, Early 2015)`, `OSX Version 10.11.6 (15G1217)`, `Apple LLVM version 8.0.0 (clang-800.0.42.1)`  

## 实验
### src_comm  
提供了一些通用/公用的头文件include, macro等, 方便使用.目前未单独编译.   

- comm_include.h  
通用的头文件include, macro等.  

### marco_test  
确认下各个编译器下新的宏的一些定义与使用. 如`__cplusplus`, 理论上支持`C++11`的编译器值至少应是`201103L`. 原`C++98/03`的此宏定义值为`199711L`.  

- macro_check.cc  
代码文件, 编译时不支持`C++11`则编译报错. 打印`__cplusplus`宏的值, `STDC`相关的几个宏, `__VA_ARGS__`宏用法, `__func__`宏等.  

- `Windows`上测试
通过`cc_test.sln`打开后选择`marco_test`为启动项目, 编译运行即可. 

- `Linux`/`MacOSX`上测试  
`[g++|clang++] -m32 -std=c++11 macro_check.cc`  
`./a.out`  

- 关于`__cplusplus`值在各平台编译器上的定义结论  
  - `VS2015`: 仍然为`199711L`, 而不是`201103L`. 看网上有人说可能是因为还未完全支持`C++11`特性, 所以微软还没有去修改此值. 故在使用`Visual Studio`时建议通过`_MSC_VER`宏来区分.  
  	 - //MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)  
	 - //MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)  
	 - //MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)    
	 - //MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)  
	 - //MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)  
	 - //MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)  
	 - //MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)  
	 - //MSVC++ 7.0  _MSC_VER == 1300  
	 - //MSVC++ 6.0  _MSC_VER == 1200  
	 - //MSVC++ 5.0  _MSC_VER == 1100  

  - `GCC`/`clang`: `201103L`, 测试版本 `gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-4)` on `CentOS7`, `clang-800.0.42.1` on `OSX 10.11.6`. 

### static_assert_test
静态断言的使用尝试, 分别应用于了枚举值的检查及模板函数中的长度检查.  

- static_assert_test.cc  
代码文件, 断言错误则编译时报错, 并输出错误信息.  

- 小技巧  
可以调用无关的断言检查, 应独立于调用外面, 以增强代码的可读性.  

- `BOOST`中提供的一份可在`C++98`使用的静态断言实现  
	主要问题:  
	- 不能显示的提示错误位置和内容  
	- 不能独立写在调用代码外面, 必须写在调用里面  

### noexcept_test
新增关键字`noexcept`用法的尝试.  

- noexcept_test.cc  
代码文件, 包含两个TestCase及`noexcept`作为操作符时的用法示例.  

- NOTE  
	- 断言适用于排除逻辑上不可能存在的状态, 异常则通常适用于可能发生的错误; 
	- `noexcept`关键字作为修饰符时, 用于指定函数是否可能会抛出异常; 作为操作符时, 则用于判断表达式是否可能会抛出异常, 多用于模板中;  
	- `C++98`中的`throw()`被`noexcept`替代, 显示指定抛出异常的类型`throw(type 1, ...)`则已在`C++11`中废弃;  
	- `delete/delete[]/析构函数`默认都是不抛出异常的, 以阻止异常扩散;  
	- 声明为`noexcept`的函数, 若抛出了异常, 则程序直接调用`std::terminate()`以暴力结束进程.  

### in-class initialization test
`C++11`中更强大的“就地”声明/初始化.  

- inclass_initialization_test.cc  
代码文件, `=`, `{}`的简单用法.  

- NOTE  
	- `C++98`仅支持静态整型/枚举型常量成员变量的就地初始化;  
	- `C++11`可支持非静态的成员变量的就地初始化, 同时支持`=`,`{}`两种形式;  
	- 关于静态成员变量的默认初始化, `C++11`与`C++98`一致, 均需要在头文件以外进行初始化, 以保证实现的唯一性.  

### sizeof_test  
`C++11`中对`sizeof`操作符的扩展, 可支持直接取非静态成员变量的长度.  

- sizeof_test.cc  
代码文件, 包含`C++11`中的新用法, 及之前编译器版本的技巧性方法.  

### friend_test  
`C++11`中`friend`关键字用法的变化, 可扩展支持模板类的`friend`声明.  

- friend_test.cc  
代码文件, 模板进行`friend`声明的示例, 编译运行时加上`UNIT_TEST`宏以观察效果.  

- using起别名(也是`C++11`中的一个新特性)  
`using Defender = DefenderT<int>`  
等同于  
`typedef DefenderT<int> Defender`  

### inherit_constructor
`C++11`中使用`using`声明来允许派生类对象直接使用基类的函数及成员. 包括普通函数/构造函数等.  

- inherit_constructor_test.cc  
代码文件, 多个`TestCase`尝试了`using`继承的使用, 及从多个基类进行派生时冲突的解决.  

- NOTE  
	- 继承时函数重名则重载  
	- 函数的默认参数不会被继承, 而是根据可能的调用情况, 继承所有的可能调用形式  
	- 从多个基类进行派生时, 若冲突则应显式定义冲突的构造函数以解决, 且指定调用基类的构造函数的版本, 否则总是会调用基类的默认构造函数
	- 从多个基类进行派生时, 总是根据继承顺序来决定调用基类构造函数的顺序, 而与`using`声明甚至显式指定调用构造函数的顺序无关  

### delegating_constructor  
`C++11`中的委托构造方法示例, 非常方便的用法.  
  
- delegating_constructor_test.cc  
代码文件, 典型的委托构造用法, 及一个简单的用模板构造函数作为target contructor的示例.  

- Note  
	- 委托构造与列表初始化不能同时使用  
	
	
### rvalue_reference  
`C++11`中的右值引用与移动语义.  

- main.cc, UnitTest.cc/h  
测试代码的入口与框架.  

- HasPtrMem.cc/h, Copyable.cc/h, Moveable.cc/h  
带有指针成员的类, 实现其拷贝构造/移动构造的代码, 包含移动构造的语义传递.  

- perfect_forwarding.cc/h  
完美转发的简单实验, 主要为模板中的使用.  

- 关键点  
	- 我理解的构造语义的触发条件: 使用右值对象/右值引用构造另外一个对象  
	- 对应的, 我理解的拷贝构造语义的触发条件: 使用左值对象/左值引用构造另外一个对象  
	- 通常的左/右值判断方法  
		- 左值(lvalue): 方法1, `=`左边即为左值; 方法2, 可以取地址、有名字则为左值  
		- 右值(rvalue): 方法1, `=`右边即为右值; 方法2, 不能取地址、没有名字则为右值  
	- `C++11`中的三种值(所有的值均属于这三者之一)  
		- 纯右值(pure rvalue): 1) 临时变量 2) 不与对象关联的值  
		- 将亡值(expiring rvalue): 将要被移动的对象  
		- 左值(rvalue): 剩余的其他值均属于左值   
	- 对右值的引用会加上其生命周期, 与引用名一致  
	- 引用类型: 
		- 左值引用(`T&`)、常量左值引用(`const T&`)、右值引用(`T&&`)、常量右值引用(`const T&&`)  
		- `const T&` 左值引用为一个万能引用类型, 可以引用任意一种引用类型  
		- 注意: 右值引用(rvalue reference) 本身是一个左值  
	- `std::move` 强制转换一个左值为右值引用, 以触发移动语义  
	- 拷贝构造函数、移动构造函数应分别根据是否需要拷贝语义、移动语义进行提供, 一般仅具有移动语义的成员变量通常为资源型, 由于不能复制      
	- 拷贝构造函数通常应提供参数为 `const T&` 的版本, 更通用  
	- `std::move/std::forward/static_cast<T&&>`基本等同, 但建议在触发移动语义时使用`move`, 完美转发时采用`forward`, 按照标准库建议的方式  
	- `C++11`的引用折叠规则(参考 3.3.6 完美转发 perfect forwarding)  
	
- 其他  
	- `VS2015`不支持关闭`Return Value Optimize`, 而此优化对本实验的影响很大, 故主要使用`GCC/clang`进行实验  
	- `GCC/clang`编译命令(打开or关闭`HAS_MOVE_CONSTRUCTOR`宏进行拷贝构造/移动构造的区别实验)  
	`[g++|clang++] -std=c++11 -I../src_comm/ [-DHAS_MOVE_CONSTRUCTOR] -fno-elide-constructors HasPtrMem.cc UnitTest.cc Copyable.cc Moveable.cc perfect_forwarding.cc main.cc`  
	- 可使用`is_reference/is_lvalue_reference/is_rvalue_reference`等几个小工具判断是何种引用类型(`UnitTest.cc->TestCase3()`)  
	- 可使用`is_move_constructible`等几个小工具判断是否有移动语义(`UnitTest.cc->TestCase8()`)  

### pod_test  
`C++`中的`POD`概念(Plain Old Data)的理解, 包括`Trivial`和`Standard Layout`两个子概念, 示例代码.  

- pod_test_types.h  
各种示例的`Trivial`, `Standard Layout`, `POD`类型的定义, 主要来源于书上.  

- main.cc  
入口及对各种定义的类型的判断示例.  

- 关键点
	- `C++11`中的`POD`类型, 需同时满足`Trivial`和`Standard Layout`两个条件  
	- `POD`的主要意义为
		- 与`C`的互操作性(兼容性), 可字节赋值, 可安全地使用`memset/memcpy`等操作之    
		- 可安全的静态初始化  
	- 类型是否为`Trivial`的判断条件
		- 对于构造函数, 拷贝构造函数, 移动构造函数, 析构函数, 拷贝赋值运算符, 移动赋值运算符而言, 
			- 要么未显式定义(由编译器自动生成默认的版本)
			- 要么显式定义但加上`=default`关键字(参考后续的第七章讲述)
		- 不能包含虚函数及虚基类
		
	- 类型是否为`Standard Layout`的判断条件  
		- 所有非静态成员需要有相同的访问权限(public, private, protected)  
		- 满足下面两个条件之一(我自己的翻译)  
			- 最多派生程度的类(也即最后的派生类)没有非静态成员, 并且最多一个基类有非静态成员  
			- 或者 没有基类有非静态成员(也即派生类可以有非静态成员了)  
			
			摘抄下标准的英文原文:  
			either has no non-static data members in the most derived class and at most one base class with non-static data memembers, or has no base classes with non-static data members  
	
	        (关于这段英文中"in the most derived class"的解释: most修饰derived class, 表示最高级的意思, 也即字面意思为 最高级的衍生类)  
		
		- 类中的第一个非静态成员的类型与基类不同  
		- 没有虚函数和虚基类  
		- 递归定义: 所有非静态数据成员均为符合`Standard Layout`的类型, 其基类也符合`Standard Layout`    
	
	- 可通过`std::is_trivial<T>, std::is_standard_layout<T>, std::is_pod<T>`这几个模板来进行是否的判断  
	
### explicit_test
`explicit`关键字使用尝试的示例. 

- main.cc  
入口及示例代码.  

- 关键点  
	- `explicit`关键字用于禁止隐式类型转换  
	- `explicit`只对一个实参的构造函数有效. 需要多个实参的构造函数不能用于执行隐式转换, 所以无须将这些构造函数指定为`explicit`的. (摘自 《C++ Primer 5th》 P.265)  
	- `explicit`只能在类内声明时使用  
	- `C++11`中`explicit`关键字同时扩展到了自定义的类型转换操作符上, 以支持所谓的“显式类型转换”.  
  
### initializer_list  
`initializer_list`的使用尝试的示例, 包括使用列表初始化普通变量、容器类等, 以及使用`initializer_list<T>`使自定义类型支持列表初始化, 列表初始化在`Narrowing`(类型收窄)时的表现等.  

- main.cc  
入口及Test Case代码, 同时包括以`intializer_list<T>`作为函数参数/返回值等.  

- ILMyData.cc/h, ILPeople.cc/h  
自定义类型基于`initializer_list<T>`来支持列表初始化, 并与操作符重载(`[]/=`)组合后的所见即所得的初始化方式.  

- 关键点  
	- `initializer_list`可用于普通变量初始化/容器类型初始化/自定义类型初始化等;  
	- `C++11`中的几种初始化方式:  
		- `=`加上赋值表达式, 如 `int a = 3 + 4;`  
		- `=`加上花括号(列表初始化), 如`int a = {3 + 4};`  
		- 圆括号, 如`int a = (3 + 4);`  
		- 花括号(列表初始化), 如`int a {3 + 4};`  
		其中后两种方式可用于堆内存上的初始化, 如`int * b = new int(10); double* d = new double {1.2f};`  
	- 自定义类型/函数参数/函数返回值支持列表初始化的方式:  
		(`C++11`内部的STL支持列表初始化也是采用的这个方法)  
		`include <intializer_list>`, 然后定义一个 `initializer_list<T> ` 作为参数的函数/构造函数或作为返回值的函数  
	- `initializer_list`列表初始化方法与其他初始化方式相比的重要优势: 防止类型收窄  
		- 类型收窄(Narrowing)的含义: 简单理解即初始化变量时会丢失精度/表达不完整  
		- 如何防止类型收窄: 原编译器通常会报warning, 而在`C++11`中采用列表初始化, 则编译器将报error, 以更好的保证安全性. (注: 实测下来, `vs2015/clang`报错了，但`GCC`并没有...)  

### Unresricted_Union
`C++11`中对于`Union`使用的扩展, 包括可支持非POD类型成员, 可支持静态成员函数(仅非匿名Union)等.  

- main.cc  
入口及测试代码, 尝试了`Unrestricted_Union`的用法, 及验证了初始化时的一些行为.  

- 关键点  
	- `Unrestricted_Union`可支持非POD类型成员, 在非匿名时同时可支持静态成员函数;  
	- `Unrestricted_Union`的初始化行为, 如`T t = {0}`时, 默认类似于`memset(&t, 0, sizeof(t))`, 但若`T t = {1}`时, 默认行为为初始化`t`第一个成员, 其他成员相当于未初始化. 使用时需要注意;  
	- `Unrestricted_Union`含有非POD类型成员时, 默认构造函数会被移除, 需通过`placement new`的方式显式定义构造函数;   

- 其他  
	- 在静态成员的支持上, vs2015与GCC又有所不同. GCC与标准一致, 不能有静态成员变量, 仅支持静态成员函数, 但vs2015可以支持`const static`的静态成员变量..  

### user_defined_literal  
`C++11`中允许用户自定义字面量的方便用法尝试.  

- main.cc  
入口及测试代码.  

- 关键点  
	- `C++11`中支持用户自定义Literal的方式, 是定义其Literal函数;  
	- Literal函数的形参可支持整型(仅`unsigned long long`), 浮点数(仅`long double`), `const char*`, `char`四种;  
		- 整型和浮点型若实参超过了`unsigned long long/long double`的表示范围, 则会自动调用`const char*`版本;  
		- 形参为`const char*`的函数, 参数表还会自带一个`size`, 由编译器自动解析填入;  
	- 杂项  
		- Literal函数声明时`""`与`_C`之间需要有空格(实验下来vs2015无所谓, 但GCC要求有);  
		- 一般建议以下划线开始为后缀, 以免与内置的如L/LL/f等后缀冲突;  

## Reference Links
- http://stackoverflow.com/questions/70013/how-to-detect-if-im-compiling-code-with-visual-studio-2008

### Contacts
Author's Email: wangyoucao577@gmail.com.
