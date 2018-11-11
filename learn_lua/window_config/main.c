#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define MAX_RGB_VALUE 255
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

struct color_table_t {
    char *name;
    struct RGB_t color;
} color_table[] = {
    {"WHITE", {MAX_RGB_VALUE, MAX_RGB_VALUE, MAX_RGB_VALUE}},
    {"RED", {MAX_RGB_VALUE, 0, 0}},
    {"GREEN", {0, MAX_RGB_VALUE, 0}},
    {"BLUE", {0, 0, MAX_RGB_VALUE}},
    // other pre-defined colors... 
    // ...
    {NULL, {0, 0, 0}}   // 哨兵
};

// 从Lua中取出变量`var_name`的值并通过virtual stack传递到C中
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

// 从Lua中取出栈顶的table中`key`对应的值并传递到C中
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

// 往Lua中栈顶的table中插入`key=value`
// 调用时table应位于栈顶
void setcolorfield(lua_State *L, const char* key, int value) {
    lua_pushstring(L, key);
    lua_pushnumber(L, (double)value / MAX_RGB_VALUE);
    lua_settable(L, -3);    // set t[key] = value
}

// 在Lua中新建table, 并用color_table中的key/value进行初始化
void setcolor(lua_State *L, struct color_table_t* ct) {
    if (!ct) {
        return;
    }

    lua_newtable(L);    // create a new table
    setcolorfield(L, "red", ct->color.red);
    setcolorfield(L, "green", ct->color.green);
    setcolorfield(L, "blue", ct->color.blue);
    lua_setglobal(L, ct->name);     // set `name` = the new table
}

int load_config(struct config_t* cfg, const char* file_path) {
    assert(cfg && file_path);

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // 初始化pre-defined colors
    // MUST be called before call .lua to initialize runtime for .lua
    for (int i = 0; color_table[i].name != NULL; ++i) {
        setcolor(L, &color_table[i]);
    }

    int err = luaL_loadfile(L, file_path) || lua_pcall(L, 0, 0, 0);
    if (err != LUA_OK) {
        luaL_error(L, "load config file %s err: %s", file_path, lua_tostring(L, -1)); // will not return
    }

    // Load configurations

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