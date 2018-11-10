
-- 初始化窗口大小
width = 200
height = 200

if os.getenv("DISPLAY") == "LARGER" then
    width = 300
    height = 300
end