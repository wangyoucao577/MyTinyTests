
#include <math.h>

#include "l_sin.h"

int l_sin(lua_State *L){
    double d = luaL_checknumber(L, 1); // 从栈中获取参数
    lua_pushnumber(L, sin(d));  // 返回值压入栈
    return 1;
}
