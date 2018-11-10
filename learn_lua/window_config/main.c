#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int getglobalint(lua_State *L, const char* var_name) {
    lua_getglobal(L, var_name);

    int result = 0;
    if (!lua_isinteger(L, -1)){
        luaL_error(L, "%s is not a integer", var_name);   // will not return
    }
    
    result = lua_tointeger(L, -1);
    lua_pop(L, 1);
    
    return result;
}

struct config_t {
    int width;
    int height;
};

int load_config(struct config_t* cfg, const char* file_path) {
    assert(cfg && file_path);

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    int err = luaL_loadfile(L, file_path) || lua_pcall(L, 0, 0, 0);
    if (err != LUA_OK) {
        luaL_error(L, "load config file %s err: %s", file_path, lua_tostring(L, -1)); // will not return
    }

    cfg->width = getglobalint(L, "width");
    cfg->height = getglobalint(L, "height");

    lua_close(L);
    return 0;
}

int main(int argc, char* argv[]) {

    char * file_path = "config.lua";    //default
    if (argc >= 2) {
        file_path = argv[1];
    }
    
    struct config_t cfg;
    load_config(&cfg, file_path);
    printf("loaded width %d height %d\n", cfg.width, cfg.height);

    return 0;
}