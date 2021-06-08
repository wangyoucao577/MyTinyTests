# identical template symbols

## 问题来源
最近和人聊时被问到的一个问题: `c++`中如果定义了重名函数，链接时会报重复定义的错误。但是模板在编译时实例化，多个`cpp`会分别自己实例化用到的模板，为什么可以正常通过链接过程？    

## 实验环境
```bash
$ cat /etc/os-release
PRETTY_NAME="Debian GNU/Linux 10 (buster)"
...
$ 
$ g++ --version
g++ (Debian 8.3.0-6) 8.3.0
...
```

## 实验过程
[How does the linker handle identical template instantiations across translation units?](https://stackoverflow.com/questions/44335046/how-does-the-linker-handle-identical-template-instantiations-across-translation) 对这个问题解释的非常清楚，实验过程即重复其过程。    

```bash
$ g++ -c -save-temps boo.cpp
$ g++ -c -save-temps foo.cpp
$ g++ -c main.cpp
$ 
$ g++ -o prog main.o foo.o boo.o -Wl,--trace-symbol='_ZNK5thingIjE2idEv',-M=prog.map
/usr/bin/ld: foo.o: definition of _ZNK5thingIjE2idEv
/usr/bin/ld: boo.o: reference to _ZNK5thingIjE2idEv
$ ./prog

f00
f00
$ g++ -o prog main.o boo.o foo.o -Wl,--trace-symbol='_ZNK5thingIjE2idEv',-M=prog.map
/usr/bin/ld: boo.o: definition of _ZNK5thingIjE2idEv
/usr/bin/ld: foo.o: reference to _ZNK5thingIjE2idEv
$ ./prog

b00
b00
```

## 我的理解
- 首先，`c++`的代码编译的几个过程顺序为：预处理 => 编译 => 链接;    
- 编译针对每个`cpp`执行，模板的实例化即在编译任意一个具体的`cpp`时触发，并将符号记录在编译生成的`.o`文件中;   
- 模板实例化的符号和普通的符号有点不同的是，模板实例化生成的符号为`weak symbol`，链接器可以自行决定在发现重复符号时对其的处理，`g++`的默认行为为选择第一个找到的符号，丢弃其他的(实验过程中也能看的出来); 但其他编译器如何处理，取决于编译器的具体实现，比如也可能选择最后一个这样的策略;      

### 其他
- `weak symbol`的另一个很重要的作用，即可以允许链接时找不到定义，从而在运行时注入实现;    
- [Weak symbol](https://en.wikipedia.org/wiki/Weak_symbol)中提到的`In contrast, in the presence of two strong symbols by the same name, the linker resolves the symbol in favor of the first one found.`貌似并不正确。两个`strong symbol`编译器应该会报重复符号定义的错误? 还是depends on具体的编译器实现?    

## References
- [How does the linker handle identical template instantiations across translation units?](https://stackoverflow.com/questions/44335046/how-does-the-linker-handle-identical-template-instantiations-across-translation)    
- [Weak symbol](https://en.wikipedia.org/wiki/Weak_symbol)
- [Duplicate c++ template instantiations](https://stackoverflow.com/questions/5537378/duplicate-c-template-instantiations)
