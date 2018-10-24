#!/usr/bin/lua


local c_func1 = package.loadlib("./c_module/libc_module.so", "exported_c_func1")

c_func1()
