
#ifndef CALL_VA_H_
#define CALL_VA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int call_va(lua_State *L, const char* lua_func_name, const char* fmt, ...);

#endif