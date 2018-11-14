
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include "l_dir.h"

int l_dir(lua_State *L) {
    
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