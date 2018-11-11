
-- 初始化窗口大小
width = 200
height = 200

if os.getenv("DISPLAY") == "LARGER" then
    width = 300
    height = 300
end

-- 背景颜色
-- BLUE = {red = 0, green = 0, blue = 1.0}
-- RED = {red = 1.0, green = 0, blue = 0}

-- BLUE, RED, GREEN, WHITE have been defined by C functions
background = BLUE
