# [C] c_interpositioning

## 实验来源与目的：  
刚看到《Expert C Programming》 5.4 警惕Interpositioning问题, 虽然说书上说的是要小心, 但这个方法却是由ANSI C标准要求编译器提供的功能. 貌似有点奇怪嘛. 好奇, 实验下看看会不有什么新发现. 

## 实验过程：
我理解Interpositioning问题的核心为用自己实现的函数替换系统函数,  那就来做个实验试试看. 

#### 实验环境：

* CentOS7 64bit, Kernel 3.10.0-229.el7.x86_64
* gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-4)
* GNU C Library (GNU libc) stable release version 2.17, by Roland McGrath et al.

#### 实验1：尝试hack `glibc`中的 `printf`

* `glibc`中最常用的恐怕就是`printf`函数了, 那么就用`printf`函数来做实验吧. 
* 首先, 实现一个`libprintf_hack.c`文件
* 可以看到, 此`printf`函数定义与`glibc`中的函数完全一致, 不同的是其实现内容为引用了一下`glibc`中的`printf`，并忽略传入参数而打印`hacked glibc printf`.
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/1.png)
* 然后，我们需要一个`main`,  实现如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/2.png)
* 可以看到, `main`的实现非常简单, 仅一句`printf`而已
* 编译执行如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/3.png)
* 奇怪, 为啥`LD_PRELOAD` 之后还是没有输出预期的`hacked glibc printf`呢？
* 分析一下看看
* 首先看下`main1`里面引用了哪些`Symbol`
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/4.png)
* main1中都没有引用到`printf`的符号, 那么hack不了也就是很正常的了. 但为什么main1中会没有`printf`的符号呢? 
* 猜测一下,  莫非`printf`不带参数时编译器会自动将其转换为`puts`实现? 否则也解释不了main1中为什么会需要`puts`的符号. 试一下.
* 实现`main2`如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/5.png)
* 编译执行如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/6.png)
* 果然如此, 与猜测一致, `printf`加上参数调用后就成功hack了
* 再确认下mian2的符号, 已经对动态库的依赖
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/7.png)
* Done! 

#### 实验2: 尝试hack `glibc`中的 `strcmp`

* `strcmp`也是一个非常常用的字符串处理函数, 再来实验下试试
* 首先, 实现`libstrcmp_hack.c`和`main3.c`如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/8.png)
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/9.png)
* 编译执行如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/10.png)
* 再次遇到不符合预期的情况, 分析下看看
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/11.png)
* 感觉还是像编译器做了什么事情, 使得main3并没有实际需要用到`strcmp`符号. 
* 再回顾下main3的源码, `strcmp`的两个参数都是常量, 所以是不是确实可以编译器自动优化? 
* 修改main再试下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/12.png)
* 编译执行如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/13.png)
* Done! 

#### 实验3: 尝试hack `glibc`中的 `malloc`和`free`

* 构建main5.c和libhack.c两个源码文件, 实现如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/14.png)
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/15.png)
* 编译运行如下
* ![](https://github.com/wangyoucao577/MyTinyTests/blob/master/c_interpositioning/pic/16.png)
* Done!

## 实验结论：

* `C`语言提供的Interpositioning, 也即LD_PRELOAD方法, 在hack或替换符号调试时还是很方便的, 但要注意符号是否被编译器优化掉从而无法hack; 如实验1和2中的`strcmp`和`printf`;
* 实际工程中还是应规避此用法, 防止出来一些非常难调试的问题; 
* 应仅限于调试使用;
* Hack后依然可以通过`dlsym`调用原系统库中的实现, 从而可以在调试时在原功能的基础上插入额外的功能代码;

## 遗留问题：

* 实验1中, `LD_PRELOAD ldd`后结果先打印了两次cannot be preloaded, ignored. Why? 
* 实验3中, 多出来的几个`hack free`的来源? 

## 实验源码：

* https://github.com/wangyoucao577/MyTinyTests/tree/master/c_interpositioning

## Reference Links:

* 5.4 Interpositioning问题 && 5.5 产生链接器报告文件 (from 《Expert C Programming》)
* 使用LD_PRELOAD来mock系统函数
* http://linmingren.me/2013/12/15/e4-bd-bf-e7-94-a8ld-preload-e6-9d-a5mock-e7-b3-bb-e7-bb-9f-e5-87-bd-e6-95-b0/

### Contacts
Author's Email: wangyoucao577@gmail.com.







