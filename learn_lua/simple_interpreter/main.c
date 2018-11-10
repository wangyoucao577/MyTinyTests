
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


void stack_dump(lua_State *L) {

    int top = lua_gettop(L);    
    for (int i = 1; i <= top; i++) {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TNUMBER:
                printf("%g", lua_tonumber(L, i));
                break;
            case LUA_TBOOLEAN:
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TSTRING:
                printf("'%s'", lua_tostring(L, i));
                break;
            case LUA_TNIL:
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
}

int main() {
    
    lua_State *L = luaL_newstate(); // create a new state for all next Lua calls   
    luaL_openlibs(L);       // open all lua standard libs

    char buff[256];
    while (fgets(buff, sizeof(buff), stdin)) {
        int err = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);    // pass buff string into state stack as Lua chunk, then call it by protect mode
        if (err != LUA_OK) {
            //stack_dump(L);
            fprintf(stderr, "%s\n", lua_tostring(L, -1));   // print error string if occurred
            lua_pop(L, 1);  // pop the error msg from state stack
        }
    }

    lua_close(L);   // release the state stack at the end
    return 0;
}
