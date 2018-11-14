# Learn Lua
学习`Lua`的基本使用, 以及与`C`的互操作.    

## 实验环境
- `Linux`:    
    - `Ubuntu 18.04 LTS`(`WSL(Windows Subsystem for Linux) on Win10 1803-17134.228`)    
    - `Lua 5.3.3  Copyright (C) 1994-2016 Lua.org, PUC-Rio`
    - `gcc (Ubuntu 7.3.0-16ubuntu3) 7.3.0`    

## 实验代码   
- `module1.lua, module1_test.lua`: `lua`中的模块以及模块的调用    
`$ ./module1_test.lua`    

- `c_module/c_module.c, c_module_test.lua`: `lua`调用`C`的`so`    
```
$ cd c_module
$ gcc -fPIC -shared c_module.c -o libc_module.so
$ cd ..
$ ./c_module_test.lua
```

- simple_interpreter: 一个简单的`Lua`解释器    
通过`C`命令行交互地获取`Lua`指令, 并实时编译传递给`Lua`进行执行. 同时引入了《Programming in lua - 4th》 ch29.1 & 29.3 中介绍的将`C`语言中实现的函数注册到`Lua`中使用的方法(`l_sin`-->`mysin`, `l_dir`-->`mydir`), 分别尝试了直接将代码写在解释器中, 以及作为`C lib`支持通过`require`导入两种方法. 最后, 基于`upvalue`实现了一把`closure`(`newcounter()`).      
```
gcc -fPIC -shared mylib.c -o mylib.so `pkg-config --cflags --libs lua5.3` -lm
gcc main.c `pkg-config --cflags --libs lua5.3` 
./a.out
> m1 = require "math"
> m2 = require "mylib"
> print(m1.sin(5))
> print(m2.mysin(5))
>
> for k,v in pairs(m2.mydir(".")) do print(v) end
>
> c1 = m2.newcounter()
> print(c1())
> print(c1())
> print(c1())
> c2 = m2.newcounter()
> print(c2())
> print("c1(): " .. c1() .. ", c2(): " .. c2())
```

- stack_dump: 通过`C API`对虚拟栈进行操作及观察    
```
gcc main.c `pkg-config --cflags --libs lua5.3`
./a.out
```

- window_config:     
《Programming in lua - 4th》ch28.1 & ch28.2 的小示例, 用`Lua`作为配置文件来使用, 包括对`Lua`中`table`的一些操作和使用.    
```
gcc main.c `pkg-config --cflags --libs lua5.3`
./a.out config.lua
env DISPLAY=LARGER ./a.out config.lua
./a.out err_config.lua
```

- call_lua_func:    
《Programming in lua - 4th》ch28.3 & ch28.4 的小示例, 用`C`调用`Lua`中的函数, 通过`virtual stack`传递参数和返回值. 实现了专门的`wrapper`和更加灵活和相对通用的`wrapper`两种形式.     
```
gcc call_va.c main.c `pkg-config --cflags --libs lua5.3`
./a.out
```

## References
- https://www.lua.org
- https://www.lua.org/manual/5.3/manual.html
- https://www.lua.org/start.html
- http://www.runoob.com/lua/lua-tutorial.html

