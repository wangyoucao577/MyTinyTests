
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main() {

    char buff[256];
    int err;
    lua_State *L = luaL_newstate(); // create a new state for all next Lua calls   
    luaL_openlibs(L);       // open all lua standard libs

    while (fgets(buff, sizeof(buff), stdin)) {
        err = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);    // pass buff string into state stack as Lua chunk, then call it by protect mode
        if (err != LUA_OK) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));   // print error string if occurred
            lua_pop(L, 1);  // pop the error msg from state stack
        }
    }

    lua_close(L);   // release the state stack at the end
    return 0;
}