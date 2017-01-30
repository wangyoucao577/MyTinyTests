# [C++11] cc11
C++11新特性尝试的一些代码及工程集合.  

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


## Reference Links
- http://stackoverflow.com/questions/70013/how-to-detect-if-im-compiling-code-with-visual-studio-2008

### Contacts
Author's Email: wangyoucao577@gmail.com.
