#!/usr/bin/lua

-- require 的模块名是 文件名 去掉后缀
-- 可以为导入的内容起个别名(即 module1.lua 中 return 的内容的别名)
local m1 = require("module1")  

-- 调用的模块名是 其中定义的非`local`的内容
print(module.constant)

module.func3()

m1.func1()


