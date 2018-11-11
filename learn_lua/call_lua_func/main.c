#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// 调用`Lua`中定义的函数`f`
double f (lua_State *L, double x, double y) {

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

    printf("f(%g, %g) = %g\n", 1.0, 1.0, f(L, 1.0, 1.0));


    lua_close(L);
    return 0;
}