#include <lua.h>
#include <lauxlib.h>

#if LUA_VERSION_NUM < 502
#ifndef luaL_newlib
# define luaL_newlib(L,l) (lua_newtable(L), luaL_register(L,NULL,l))
#endif
# define luaL_setfuncs(L,l,n) (assert(n==0), luaL_register(L,NULL,l))
#endif

#ifdef _WIN32
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

static int luawindcon_clear(lua_State* L)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return luaL_error(L, "failed to get stdout handle");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return 0;

    DWORD area = csbi.dwSize.X * csbi.dwSize.Y;
    COORD topLeft = { 0, 0 };
    DWORD count;

    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        area,
        topLeft,
        &count
    )) return 0;

    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        area,
        topLeft,
        &count
    )) return 0;

    SetConsoleCursorPosition(hStdOut, topLeft);

    lua_pushboolean(L, 1);
    return 1;
}

static int luawindcon_size(lua_State* L)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return luaL_error(L, "failed to get stdout handle");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        return 0;

    lua_pushinteger(L, csbi.dwSize.X);
    lua_pushinteger(L, csbi.dwSize.Y);
    return 2;
}

static int luawindcon_movecursor(lua_State* L)
{
    int x = luaL_checkint(L, 1);
    int y = luaL_checkint(L, 2);

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return luaL_error(L, "failed to get stdout handle");

    COORD newPos = { x, y };
    if (!SetConsoleCursorPosition(hStdOut, newPos)) {
        lua_pushnil(L);
        lua_pushfstring(L, "failed to move cursor to (%d,%d)", x, y);
        return 2;
    }

    lua_pushboolean(L, 1);
    return 1;
}

static int luawindcon_showcursor(lua_State* L)
{
    // default to true if not specified
    BOOL shouldShow = !lua_isnoneornil(L, 1) ? lua_toboolean(L, 1) : TRUE;
    CONSOLE_CURSOR_INFO curInfo;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return luaL_error(L, "failed to get stdout handle");

    GetConsoleCursorInfo(hStdOut, &curInfo);
    if (curInfo.bVisible != shouldShow) {
        curInfo.bVisible = shouldShow;
        SetConsoleCursorInfo(hStdOut, &curInfo);
    }

    lua_pushboolean(L, 1);
    return 1;
}

static const luaL_Reg luawindcon_funcs[] = {
    { "movecursor", luawindcon_movecursor },
    { "showcursor", luawindcon_showcursor },
    { "clear", luawindcon_clear },
    { "size", luawindcon_size },
    { NULL, NULL }
};

EXPORT int luaopen_windcon(lua_State *L)
{
    luaL_newlib(L, luawindcon_funcs);
    return 1;
}