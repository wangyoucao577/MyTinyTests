

#include "call_va.h"

int call_va(lua_State *L, const char* lua_func_name, const char* fmt, ...){

    lua_getglobal(L, lua_func_name);    // Lua 函数压栈

    va_list vl;
    va_start(vl, fmt);

    // push parameters
    int narg = 0;
    for (narg = 0; *fmt; narg++) {
        // 检查栈空间
        luaL_checkstack(L, 1, "stack can not store too many arguments");

        char param_type = *fmt++;
        if (param_type == '>'){
            break;  // end of parameter list
        }else if (param_type == 'd'){
            lua_pushnumber(L, va_arg(vl, double));
        }else if (param_type == 'i'){
            lua_pushinteger(L, va_arg(vl, int));
        }else if (param_type == 's'){
            lua_pushstring(L, va_arg(vl, char*));
        }else {
            luaL_error(L, "unknown paramter type: %c", param_type);
        }
    }

    int nres = strlen(fmt);

    // call function
    if (lua_pcall(L, narg, nres, 0) != 0) {
        luaL_error(L, "error calling '%s': %s", lua_func_name, lua_tostring(L, -1));
    }

    // retrieve results
    nres = -nres;   // 第一个结果在栈中的索引
    while (*fmt) {
        char param_type = *fmt++;
        if (param_type == 'd'){
            if (!lua_isnumber(L, nres)){
                luaL_error(L, "expect (double) number but actually not");
            }
            *va_arg(vl, double*) = lua_tonumber(L, nres);
        }else if (param_type == 'i'){
            if (!lua_isinteger(L, nres)){
                luaL_error(L, "expect integer but actually not");
            }
            *va_arg(vl, int*) = lua_tointeger(L, nres);
        }else if (param_type == 's'){
            const char* s = lua_tostring(L, nres);
            if (s == NULL) {
                luaL_error(L, "expect string but actually not");
            }
            *va_arg(vl, const char**) = s;
        }else {
            luaL_error(L, "unknown result type: %c", param_type);
        }
        nres++;
    }


    va_end(vl);

    //NOTE: caller has responsibility to call lua_pop for all results after use them

    return 0;
}