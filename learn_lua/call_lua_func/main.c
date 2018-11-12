
#include "call_va.h"

// 调用`Lua`中定义的函数`f`
double f_wrapper (lua_State *L, double x, double y) {

    // 函数压栈, 参数压栈
    lua_getglobal(L, "f");  // Lua中的函数`f`
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);

    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
        luaL_error(L, "error run function `f`: %s", lua_tostring(L, -1));
    }
    
    if (!lua_isnumber(L, -1)){
        luaL_error(L, "function `f` should return a number");
    }
    double ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

int main() {

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    const char* file_path = "func_sample.lua";
    int err = luaL_loadfile(L, file_path) || lua_pcall(L, 0, 0, 0);
    if (err != LUA_OK) {
        luaL_error(L, "load Lua file %s err: %s", file_path, lua_tostring(L, -1)); // will not return
    }

    // C call lua function
    double x = 1.0, y = 1.0;

    // way1. by a seprate f_wrapper
    printf("f(%g, %g) = %g ... via f_wrapper() \n", x, y, f_wrapper(L, x, y));  

    // way2. by a generic wrapper
    double result = 0.0f;
    call_va(L, "f", "dd>d", x, y, &result); 
    printf("f(%g, %g) = %g ... via call_va(f) \n", x, y, result);
    lua_pop(L, 1);  // NOTE: for this way, should pop from stack manually after call `call_va`

    lua_close(L);
    return 0;
}