#include "types.h"

#include <lauxlib.h>

static const luaL_Reg lua_onion_funcs[] =
{
	{"new", lua_onion_new},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_methods[] =
{
	{"set_root_handler", lua_onion_set_root_handler},
	{"listen", lua_onion_listen},
	{"listen_stop", lua_onion_listen_stop},
	{"root_url", lua_onion_root_url},
	{"set_session_backend", lua_onion_set_session_backend},
	{"__gc", lua_onion_free},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_handler_funcs[] =
{
	{"new", lua_onion_handler_new},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_handler_methods[] =
{
	{"__gc", lua_onion_handler_free},
	{"add", lua_onion_handler_add},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_url_funcs[] =
{
	{"new", lua_onion_url_new},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_url_methods[] =
{
	{"__gc", lua_onion_url_free},
	{"add", lua_onion_url_add},
	{"add_url", lua_onion_url_add_url},
	{"add_static", lua_onion_url_add_static},
	{"to_handler", lua_onion_url_to_handler},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_dict_funcs[] =
{
	{"new", lua_onion_dict_new},
	{"fromJSON", lua_onion_dict_fromJSON},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_dict_methods[] =
{
	{"__gc", lua_onion_dict_free},
	{"add", lua_onion_dict_add},
	{"get", lua_onion_dict_get},
	{"remove", lua_onion_dict_remove},
	{"merge", lua_onion_dict_merge},
	{"count", lua_onion_dict_count},
	{"lock_read", lua_onion_dict_lock_read},
	{"lock_write", lua_onion_dict_lock_write},
	{"unlock", lua_onion_dict_unlock},
	{"toJSON", lua_onion_dict_toJSON},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_block_funcs[] =
{
	{"new", lua_onion_block_new},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_block_methods[] =
{
	{"__gc", lua_onion_block_free},
	{"clear", lua_onion_block_clear},
	{"size", lua_onion_block_size},
	{"data", lua_onion_block_data},
	{"add", lua_onion_block_add},
	{"add_block", lua_onion_block_add_block},
	{"rewind", lua_onion_block_rewind},
	{"min_maxsize", lua_onion_block_min_maxsize},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_request_funcs[] =
{
	{NULL, NULL}
};

static const luaL_Reg lua_onion_request_methods[] =
{
	{"get_flags", lua_onion_request_get_flags},
	{"get_header", lua_onion_request_get_header},
	{"get_path", lua_onion_request_get_path},
	{"get_fullpath", lua_onion_request_get_fullpath},
	{"advance_path", lua_onion_request_advance_path},
	{"get_query", lua_onion_request_get_query},
	{"get_post", lua_onion_request_get_post},
	{"get_file", lua_onion_request_get_file},
	{"get_session", lua_onion_request_get_session},
	{"get_header_dict", lua_onion_request_get_header_dict},
	{"get_query_dict", lua_onion_request_get_query_dict},
	{"get_post_dict", lua_onion_request_get_post_dict},
	{"get_file_dict", lua_onion_request_get_file_dict},
	{"get_session_dict", lua_onion_request_get_session_dict},
	{"get_cookies_dict", lua_onion_request_get_cookies_dict},
	{"get_cookie", lua_onion_request_get_cookie},
	{"get_language_code", lua_onion_request_get_language_code},
	{"get_data", lua_onion_request_get_data},
	{"get_client_description", lua_onion_request_get_client_description},
	{"is_secure", lua_onion_request_is_secure},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_response_funcs[] =
{
	{NULL, NULL}
};

static const luaL_Reg lua_onion_response_methods[] =
{
	{"set_header", lua_onion_response_set_header},
	{"set_length", lua_onion_response_set_length},
	{"set_code", lua_onion_response_set_code},
	{"get_headers", lua_onion_response_get_headers},
	{"add_cookie", lua_onion_response_add_cookie},
	{"write", lua_onion_response_write},
	{"write_html_safe", lua_onion_response_write_html_safe},
	{NULL, NULL}
};

static const luaL_Reg lua_onion_sessions_methods[] =
{
	{NULL, NULL}
};

#ifdef HAVE_REDIS
static const luaL_Reg lua_onion_redis_sessions_funcs[] =
{
	{"new", lua_onion_redis_sessions_new},
	{NULL, NULL}
};

#endif

#ifdef HAVE_SQLITE3
static const luaL_Reg lua_onion_sqlite3_sessions_funcs[] =
{
	{"new", lua_onion_sqlite3_sessions_new},
	{NULL, NULL}
};
#endif

static int constant_function(lua_State* unused)
{
	return 0;
}

static void create_object(lua_State *L, const char* name, const luaL_Reg* methods)
{
	luaL_newmetatable(L, name);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, methods, 0);
}

static void create_request_flags_enum(lua_State *L)
{
	lua_newtable(L);
	luaL_newmetatable(L, "onion.RequestFlags");
	lua_newtable(L);

	lua_pushinteger(L, OR_METHODS);
	lua_setfield(L, -2, "METHODS");
	lua_pushinteger(L, OR_GET);
	lua_setfield(L, -2, "GET");
	lua_pushinteger(L, OR_POST);
	lua_setfield(L, -2, "POST");
	lua_pushinteger(L, OR_HEAD);
	lua_setfield(L, -2, "HEAD");
	lua_pushinteger(L, OR_OPTIONS);
	lua_setfield(L, -2, "OPTIONS");
	lua_pushinteger(L, OR_PROPFIND);
	lua_setfield(L, -2, "PROPFIND");
	lua_pushinteger(L, OR_PUT);
	lua_setfield(L, -2, "PUT");
	lua_pushinteger(L, OR_DELETE);
	lua_setfield(L, -2, "DELETE");
	lua_pushinteger(L, OR_MOVE);
	lua_setfield(L, -2, "MOVE");
	lua_pushinteger(L, OR_MKCOL);
	lua_setfield(L, -2, "MKCOL");
	lua_pushinteger(L, OR_PROPPATCH);
	lua_setfield(L, -2, "PROPPATCH");
	lua_pushinteger(L, OR_PATCH);
	lua_setfield(L, -2, "PATCH");

	lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, constant_function);
	lua_setfield(L, -2, "__newindex");
	lua_pushboolean(L, false);
	lua_setfield(L, -2, "__metatable");
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "RequestFlags");
}

static void create_response_code_enum(lua_State *L)
{
	lua_newtable(L);
	luaL_newmetatable(L, "onion.ResponseCode");
	lua_newtable(L);

	lua_pushinteger(L, HTTP_SWITCH_PROTOCOL);
	lua_setfield(L, -2, "SWITCH_PROTOCOL");
	lua_pushinteger(L, HTTP_OK);
	lua_setfield(L, -2, "OK");
	lua_pushinteger(L, HTTP_CREATED);
	lua_setfield(L, -2, "CREATED");
	lua_pushinteger(L, HTTP_PARTIAL_CONTENT);
	lua_setfield(L, -2, "PARTIAL_CONTENT");
	lua_pushinteger(L, HTTP_MULTI_STATUS);
	lua_setfield(L, -2, "MULTI_STATUS");
	lua_pushinteger(L, HTTP_MOVED);
	lua_setfield(L, -2, "MOVED");
	lua_pushinteger(L, HTTP_REDIRECT);
	lua_setfield(L, -2, "REDIRECT");
	lua_pushinteger(L, HTTP_SEE_OTHER);
	lua_setfield(L, -2, "SEE_OTHER");
	lua_pushinteger(L, HTTP_NOT_MODIFIED);
	lua_setfield(L, -2, "NOT_MODIFIED");
	lua_pushinteger(L, HTTP_TEMPORARY_REDIRECT);
	lua_setfield(L, -2, "TEMPORARY_REDIRECT");
	lua_pushinteger(L, HTTP_BAD_REQUEST);
	lua_setfield(L, -2, "BAD_REQUEST");
	lua_pushinteger(L, HTTP_UNAUTHORIZED);
	lua_setfield(L, -2, "UNAUTHORIZED");
	lua_pushinteger(L, HTTP_FORBIDDEN);
	lua_setfield(L, -2, "FORBIDDEN");
	lua_pushinteger(L, HTTP_METHOD_NOT_ALLOWED);
	lua_setfield(L, -2, "METHOD_NOT_ALLOWED");
	lua_pushinteger(L, HTTP_BAD_GATEWAY);
	lua_setfield(L, -2, "BAD_GATEWAY");
	lua_pushinteger(L, HTTP_SERVICE_UNAVAILABLE);
	lua_setfield(L, -2, "SERVICE_UNAVAILABLE");

	lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, constant_function);
	lua_setfield(L, -2, "__newindex");
	lua_pushboolean(L, false);
	lua_setfield(L, -2, "__metatable");
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "ResponseCode");
}

static void create_status_code_enum(lua_State *L)
{
	lua_newtable(L);
	luaL_newmetatable(L, "onion.Status");
	lua_newtable(L);

	lua_pushinteger(L, OCS_NOT_PROCESSED);
	lua_setfield(L, -2, "NOT_PROCESSED");
	lua_pushinteger(L, OCS_NEED_MORE_DATA);
	lua_setfield(L, -2, "NEED_MORE_DATA");
	lua_pushinteger(L, OCS_PROCESSED);
	lua_setfield(L, -2, "PROCESSED");
	lua_pushinteger(L, OCS_CLOSE_CONNECTION);
	lua_setfield(L, -2, "CLOSE_CONNECTION");
	lua_pushinteger(L, OCS_KEEP_ALIVE);
	lua_setfield(L, -2, "KEEP_ALIVE");
	lua_pushinteger(L, OCS_WEBSOCKET);
	lua_setfield(L, -2, "WEBSOCKET");
	lua_pushinteger(L, OCS_INTERNAL_ERROR);
	lua_setfield(L, -2, "INTERNAL_ERROR");
	lua_pushinteger(L, OCS_NOT_IMPLEMENTED);
	lua_setfield(L, -2, "NOT_IMPLEMENTED");
	lua_pushinteger(L, OCS_FORBIDDEN);
	lua_setfield(L, -2, "FORBIDDEN");
	lua_pushinteger(L, OCS_YIELD);
	lua_setfield(L, -2, "YIELD");

	lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, constant_function);
	lua_setfield(L, -2, "__newindex");
	lua_pushboolean(L, false);
	lua_setfield(L, -2, "__metatable");
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "Status");
}

static void create_mode_enum(lua_State *L)
{
	lua_newtable(L);
	luaL_newmetatable(L, "onion.Mode");
	lua_newtable(L);

	lua_pushinteger(L, O_ONE);
	lua_setfield(L, -2, "ONE");
	lua_pushinteger(L, O_ONE_LOOP);
	lua_setfield(L, -2, "ONE_LOOP");
	lua_pushinteger(L, O_THREADED);
	lua_setfield(L, -2, "THREADED");
	lua_pushinteger(L, O_DETACH_LISTEN);
	lua_setfield(L, -2, "DETACH_LISTEN");
	lua_pushinteger(L, O_SYSTEMD);
	lua_setfield(L, -2, "SYSTEMD");
	lua_pushinteger(L, O_POLL);
	lua_setfield(L, -2, "POLL");
	lua_pushinteger(L, O_POOL);
	lua_setfield(L, -2, "POOL");
	lua_pushinteger(L, O_NO_SIGPIPE);
	lua_setfield(L, -2, "NO_SIGPIPE");
	lua_pushinteger(L, O_NO_SIGTERM);
	lua_setfield(L, -2, "NO_SIGTERM");
	lua_pushinteger(L, O_SSL_AVAILABLE);
	lua_setfield(L, -2, "SSL_AVAILABLE");
	lua_pushinteger(L, O_SSL_ENABLED);
	lua_setfield(L, -2, "SSL_ENABLED");
	lua_pushinteger(L, O_THREADS_AVAILABLE);
	lua_setfield(L, -2, "THREADS_AVAILABLE");
	lua_pushinteger(L, O_THREADS_ENABLED);
	lua_setfield(L, -2, "THREADS_ENABLED");
	lua_pushinteger(L, O_DETACHED);
	lua_setfield(L, -2, "DETACHED");
	lua_pushinteger(L, O_LISTENING);
	lua_setfield(L, -2, "LISTENING");

	lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, constant_function);
	lua_setfield(L, -2, "__newindex");
	lua_pushboolean(L, false);
	lua_setfield(L, -2, "__metatable");

	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "Mode");
}

int luaopen_onion(lua_State *L)
{
	// Create all the objects
	create_object(L, "onion.Onion", lua_onion_methods);
	create_object(L, "onion.Url", lua_onion_url_methods);
	create_object(L, "onion.Block", lua_onion_block_methods);
	create_object(L, "onion.Dict", lua_onion_dict_methods);
	create_object(L, "onion.Request", lua_onion_request_methods);
	create_object(L, "onion.Response", lua_onion_response_methods);
	create_object(L, "onion.Handler", lua_onion_handler_methods);
	create_object(L, "onion.Sessions", lua_onion_sessions_methods);

	// Table representing this library
	lua_newtable(L);

	// Add static object methods to the library
	luaL_newlib(L, lua_onion_funcs);
	lua_setfield(L, -2, "Onion");

	luaL_newlib(L, lua_onion_url_funcs);
	lua_setfield(L, -2, "Url");

	luaL_newlib(L, lua_onion_dict_funcs);
	lua_setfield(L, -2, "Dict");

	luaL_newlib(L, lua_onion_block_funcs);
	lua_setfield(L, -2, "Block");

	luaL_newlib(L, lua_onion_request_funcs);
	lua_setfield(L, -2, "Request");

	luaL_newlib(L, lua_onion_response_funcs);
	lua_setfield(L, -2, "Response");

	luaL_newlib(L, lua_onion_handler_funcs);
	lua_setfield(L, -2, "Handler");

#ifdef HAVE_REDIS
	luaL_newlib(L, lua_onion_redis_sessions_funcs);
	lua_setfield(L, -2, "RedisSessions");
#endif

#ifdef HAVE_SQLITE3
	luaL_newlib(L, lua_onion_sqlite3_sessions_funcs);
	lua_setfield(L, -2, "Sqlite3Sessions");
#endif

	create_request_flags_enum(L);
	create_response_code_enum(L);
	create_status_code_enum(L);
	create_mode_enum(L);
	return 1;
}
