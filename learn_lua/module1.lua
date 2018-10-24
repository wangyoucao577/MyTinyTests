
-- 定义一个名为 module 的模块
module = {}

-- 定义一个常量
module.constant = "这是一个常量"

-- 定义一个函数
function module.func1()
    io.write("这是一个导出的函数!\n")
end

local function func2()
    print("这是一个局部函数!")
end

function module.func3()
    func2()
end

return module
