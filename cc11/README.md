# [C++11] cc11
C++11新特性尝试的一些代码及工程集合, 测试代码主要来源于《Understanding C++11 -- Analysis and Application of New Features》.  

## 阅读与运行
- `Windows`: 可通过`cc_test.sln`(`VS2015`)打开所有的工程及代码, 选择某个工程进行编译及运行即可.   
- `Linux`: `g++ [-m32] -std=c++11 xxx.cc` 编译, 然后运行即可  

## 实验平台
- `Windows`: `Win10 64bit`, `Visual Studio 2015 Update 3`  
- `Linux`: `CentOS7 64bit`, `Kernel 3.10.0-229.el7.x86_64`, `gcc 4.8.5 20150623`  

## 实验

### marco_test  
确认下各个编译器下新的宏的一些定义与使用. 如`__cplusplus`, 理论上支持`C++11`的编译器值至少应是`201103L`. 原`C++98/03`的此宏定义值为`199711L`.  

- macro_check.cc  
代码文件, 编译时不支持`C++11`则编译报错. 打印`__cplusplus`宏的值, `STDC`相关的几个宏, `__VA_ARGS__`宏用法, `__func__`宏等.  

- `Windows`上测试
通过`cc_test.sln`打开后选择`marco_test`为启动项目, 编译运行即可. 

- `Linux`上测试  
`g++ -m32 -std=c++11 macro_check.cc`  
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

  - `GCC`: `201103L`, 测试版本 `gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-4)` on `CentOS7`. 

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

## Reference Links
- http://stackoverflow.com/questions/70013/how-to-detect-if-im-compiling-code-with-visual-studio-2008

### Contacts
Author's Email: wangyoucao577@gmail.com.
