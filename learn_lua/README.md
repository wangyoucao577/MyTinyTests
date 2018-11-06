# Learn Lua
学习`Lua`的基本使用, 以及与`C`的互操作.    

## 实验环境
- `Linux`:    
    - `Ubuntu 18.04 LTS`(`WSL(Windows Subsystem for Linux) on Win10 1803-17134.228`)    
    - `Lua 5.2.4  Copyright (C) 1994-2015 Lua.org, PUC-Rio`
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

## References
- https://www.lua.org
- https://www.lua.org/manual/5.3/manual.html
- https://www.lua.org/start.html
- http://www.runoob.com/lua/lua-tutorial.html

