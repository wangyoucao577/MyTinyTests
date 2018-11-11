
-- 初始化窗口大小
width = 200
height = 200

if os.getenv("DISPLAY") == "LARGER" then
    width = 300
    height = 300
end

-- 背景颜色
BlueRGB = {red = 0, green = 0, blue = 1.0}
RedRGB = {red = 1.0, green = 0, blue = 0}

background = BlueRGB
