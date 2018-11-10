#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


void stack_dump(lua_State *L) {
    printf("\n\n------------ stack_dump begin ---------------\n");

    int top = lua_gettop(L);    
    for (int i = 1; i <= top; i++) {
        printf("[%d|%d] ", i, i - 1 - top);
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TNUMBER:
                if (lua_isinteger(L, i)){
                    printf("%lld", lua_tointeger(L, i));
                }else {
                    printf("%g", lua_tonumber(L, i));
                }
                break;
            case LUA_TBOOLEAN:
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TSTRING:
                printf("'%s'", lua_tostring(L, i));
                break;
            case LUA_TNIL:
                printf("NIL");
                break;
            case LUA_TTABLE:
            case LUA_TFUNCTION:
            case LUA_TUSERDATA:
            case LUA_TTHREAD:
            case LUA_TLIGHTUSERDATA:
            default:
                printf("%s", lua_typename(L, t));
                break;
        }
        printf("\n");
    }
    printf("------------ stack_dump end ---------------\n\n");
}

int main() {
    lua_State *L = luaL_newstate();
    stack_dump(L);

    // push...

    lua_pushnumber(L, 10.2);
    lua_pushinteger(L, 10);
    stack_dump(L);

    lua_pushnil(L);
    lua_pushstring(L, "push string");
    stack_dump(L);

    lua_pushboolean(L, 0);
    stack_dump(L);

    lua_pushboolean(L, 1);
    stack_dump(L);

    lua_pushboolean(L, 2);
    lua_pushboolean(L, -2);
    stack_dump(L);

    // stack operations ...

    lua_settop(L, -1);
    stack_dump(L);

    lua_settop(L, 7);
    stack_dump(L);

    lua_pushvalue(L, 2);
    stack_dump(L);

    lua_replace(L, 1);
    stack_dump(L);

    lua_rotate(L, 3, 3);
    stack_dump(L);

    lua_remove(L, 2);
    stack_dump(L);

    lua_close(L);

    // practice 27.2 & 27.3
    L = luaL_newstate();
    lua_pushnumber(L, 3.5);
    lua_pushstring(L, "hello");
    lua_pushnil(L);
    lua_rotate(L, 1, -1);
    lua_pushvalue(L, -2);
    lua_remove(L, 1);
    lua_insert(L, -2);
    stack_dump(L);
    lua_close(L);
}