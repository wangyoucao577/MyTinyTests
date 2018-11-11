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
通过`C`命令行交互地获取`Lua`指令, 并实时编译传递给`Lua`进行执行.    
```
gcc main.c `pkg-config --cflags --libs lua5.3`
./a.out
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

## References
- https://www.lua.org
- https://www.lua.org/manual/5.3/manual.html
- https://www.lua.org/start.html
- http://www.runoob.com/lua/lua-tutorial.html

