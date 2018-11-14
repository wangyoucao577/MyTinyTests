
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

/************************ 以下为将我们自己实现的两个函数通过c模块的方式导出 *********************/

// mylib支持的函数列表
static const struct luaL_Reg mylib[] = {
    {"mydir", l_dir},
    {"mysin", l_sin}, 
    {NULL, NULL}    //哨兵
};

// mylib被`require`时的打开函数
int luaopen_mylib(lua_State *L) {
    luaL_newlib(L, mylib);
    return 1;
}