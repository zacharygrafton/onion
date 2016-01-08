#include "types.h"

#include <lauxlib.h>

static lua_onion* create_new_onion(lua_State *L)
{
	lua_onion* o = lua_newuserdata(L, sizeof(lua_onion));
	luaL_getmetatable(L, "onion.Onion");
	lua_setmetatable(L, -2);
	return o;
}

static int lua_onion_new(lua_State *L)
{
	int flags = luaL_checkinteger(L, 1);
	lua_onion* o = create_new_onion(L);
	o->o = onion_new(flags);
	return 1;
}

static int lua_onion_free(lua_State *L)
{
	lua_onion* o = CHECK_ONION(L, 1);
	onion_free(o->o);
	return 0;
}

static int lua_onion_listen(lua_State *L)
{
	lua_onion* o = CHECK_ONION(L, 1);
	onion_listen(o->o);
	return 0;
}

static int lua_onion_listen_stop(lua_State *L)
{
	lua_onion* o = CHECK_ONION(L, 1);
	onion_listen_stop(o->o);
	return 0;
}

static int lua_onion_set_root_handler(lua_State *L)
{
	lua_onion* o = CHECK_ONION(L, 1);
	lua_onion_handler* handler = CHECK_HANDLER(L, 2);
	handler->owner = false;
	onion_set_root_handler(o->o, handler->handler);
	return 0;
}

static int lua_onion_root_url(lua_State *L)
{
	lua_onion* o = CHECK_ONION(L, 1);
	lua_onion_url* url = create_new_onion_url(L);
	url->url = onion_root_url(o->o);
	return 1;
}

static int lua_onion_set_session_backend(lua_State *L)
{
	lua_onion* o = CHECK_ONION(L, 1);
	lua_onion_sessions* sessions = CHECK_SESSIONS(L, 2);
	onion_set_session_backend(o->o, sessions->sessions);
	return 0;
}
