#include "types.h"

#include <lauxlib.h>
#include <onion/low.h>

static lua_onion_url* create_new_onion_url(lua_State *L)
{
	lua_onion_url* url = (lua_onion_url*)lua_newuserdata(L, sizeof(lua_onion_url));
	luaL_getmetatable(L, "onion.Url");
	lua_setmetatable(L, -2);
	url->owner = false;
	return url;
}

static int lua_onion_url_new(lua_State *L)
{
	lua_onion_url* url = create_new_onion_url(L);
	url->owner = true;
	url->url = onion_url_new();
	return 1;
}

static int lua_onion_url_free(lua_State *L)
{
	lua_onion_url* url = CHECK_URL(L, 1);
	if(url->owner == true)
		onion_url_free(url->url);
	return 0;
}

static int lua_onion_url_add(lua_State *L)
{
	lua_onion_url* url = CHECK_URL(L, 1);
	const char* route = luaL_checkstring(L, 2);
	lua_onion_handler* handler = CHECK_HANDLER(L, 3);
	onion_url_add_handler(url->url, route, handler->handler);
	return 0;
}

static int lua_onion_url_add_url(lua_State *L)
{
	lua_onion_url* base = CHECK_URL(L, 1);
	const char* route = luaL_checkstring(L, 2);
	lua_onion_url* child = CHECK_URL(L, 3);
	onion_url_add_url(base->url, route, child->url);
	return 0;
}

static int lua_onion_url_add_static(lua_State *L)
{
	lua_onion_url* url = CHECK_URL(L, 1);
	const char* route = luaL_checkstring(L, 2);
	const char* data = luaL_checkstring(L, 3);
	int code = luaL_checkinteger(L, 4);
	onion_url_add_static(url->url, route, data, code);
	return 0;
}

static int lua_onion_url_to_handler(lua_State* L)
{
	lua_onion_url* url = CHECK_URL(L, 1);
	lua_onion_handler* handler = create_new_onion_handler(L);
	handler->owner = false;
	handler->handler = onion_url_to_handler(url->url);
	return 1;
}
