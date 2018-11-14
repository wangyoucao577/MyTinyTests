
#include <math.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static int l_sin(lua_State *L){
    double d = luaL_checknumber(L, 1); // 从栈中获取参数
    lua_pushnumber(L, sin(d));  // 返回值压入栈
    return 1;
}

static int l_dir(lua_State *L) {
    
    const char *path = luaL_checkstring(L, 1);

    // open dir
    DIR *dir = opendir(path);
    if (dir == NULL) {
        lua_pushnil(L); // 返回NIL
        lua_pushstring(L, strerror(errno)); // 和 错误信息
        return 2;   // number of results
    }

    // 创建结果表
    lua_newtable(L);
    int i = 1;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        lua_pushinteger(L, i++);    // 表中的键
        lua_pushstring(L, entry->d_name);   // 键对应的value
        lua_settable(L, -3);    // 键值对set到table中
    }

    closedir(dir);
    return 1;   // table
}

/************************ closure by upvalue *********************/

static int counter(lua_State *L) {
    int val = lua_tointeger(L, lua_upvalueindex(1));
    lua_pushinteger(L, ++val);
    lua_copy(L, -1, lua_upvalueindex(1));   // update to upvalue
    return 1;
}

static int l_new_counter(lua_State *L) {
    lua_pushinteger(L, 0);
    lua_pushcclosure(L, counter, 1);
    return 1;
}

/************************ closure by upvalue *********************/


/************************ 以下为将我们自己实现的两个函数通过c模块的方式导出 *********************/

// mylib支持的函数列表
static const struct luaL_Reg mylib[] = {
    {"mydir", l_dir},
    {"mysin", l_sin}, 
    {"newcounter", l_new_counter},
    {NULL, NULL}    //哨兵
};

// mylib被`require`时的打开函数
int luaopen_mylib(lua_State *L) {
    luaL_newlib(L, mylib);
    return 1;
}