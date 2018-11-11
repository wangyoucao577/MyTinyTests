#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static const int MAX_RGB_VALUE = 255;
struct RGB_t {
    int red;
    int green;
    int blue;
};

struct config_t {
    int width;
    int height;
    struct RGB_t background_color;
};


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

// 调用时table应位于栈顶
int getcolorfield(lua_State *L, const char* key) {
    lua_pushstring(L, key);
    lua_gettable(L, -2);    // get t[key]

    if (!lua_isnumber(L, -1)) {
        luaL_error(L, "value of key %s is not a float number in table", key);
    }
    int result = (int)(((double)lua_tonumber(L, -1)) * MAX_RGB_VALUE);
    lua_pop(L, 1);
    return result;
}

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

    lua_getglobal(L, "background");
    if (!lua_istable(L, -1)){
        luaL_error(L, "'background' is not a table");
    }
    cfg->background_color.red = getcolorfield(L, "red");
    cfg->background_color.green = getcolorfield(L, "green");
    cfg->background_color.blue = getcolorfield(L, "blue");


    lua_close(L);
    return 0;
}

void dump_config(const struct config_t* cfg) {
    if (cfg == NULL) {
        return;
    }

    printf("loaded config: \n");
    printf("    width = %d\n", cfg->width);
    printf("    height = %d\n", cfg->height);
    printf("    background_color.red = %d\n", cfg->background_color.red);
    printf("    background_color.green = %d\n", cfg->background_color.green);
    printf("    background_color.blue = %d\n", cfg->background_color.blue);
}

int main(int argc, char* argv[]) {

    char * file_path = "config.lua";    //default
    if (argc >= 2) {
        file_path = argv[1];
    }

    struct config_t cfg;
    load_config(&cfg, file_path);
    dump_config(&cfg);

    return 0;
}