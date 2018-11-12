#!/usr/bin/lua5.3

function f (x, y)
    return (x ^ 2 * math.sin(y)) / x
    -- return 3.0
    -- return "str"
end

function f_bool_reverse (x)
    return not x, x
end