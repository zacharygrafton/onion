#include "types.h"

#ifdef HAVE_REDIS
#include <onion/sessions_redis.h>
#endif

#ifdef HAVE_SQLITE3
#include <onion/sessions_sqlite3.h>
#endif

#include <lauxlib.h>

static lua_onion_sessions* create_new_onion_sessions(lua_State* L)
{
	lua_onion_sessions* sessions = (lua_onion_sessions*)lua_newuserdata(L, sizeof(lua_onion_sessions));
	luaL_getmetatable(L, "onion.Sessions");
	lua_setmetatable(L, -2);
	return sessions;
}

#ifdef HAVE_REDIS
static int lua_onion_redis_sessions_new(lua_State *L)
{
	const char* server_ip = luaL_checkstring(L, 1);
	int server_port = luaL_checkinteger(L, 2);

	lua_onion_sessions* sessions = create_new_onion_sessions(L);
	sessions->sessions = onion_sessions_redis_new(server_ip, server_port);
	return 1;
}
#endif

#ifdef HAVE_SQLITE3
static int lua_onion_sqlite3_sessions_new(lua_State *L)
{
	const char* db_filename = luaL_checkstring(L, 1);

	lua_onion_sessions* sessions = create_new_onion_sessions(L);
	sessions->sessions = onion_sessions_sqlite3_new(db_filename);
	return 1;
}
#endif
