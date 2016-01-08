#include "types.h"

#include <lauxlib.h>

static lua_onion_response* create_new_onion_response(lua_State *L)
{
	lua_onion_response* response = (lua_onion_response*)lua_newuserdata(L, sizeof(lua_onion_response));
	luaL_getmetatable(L, "onion.Response");
	lua_setmetatable(L, -2);
	return response;
}

static int lua_onion_response_write(lua_State *L)
{
	lua_onion_response* response = CHECK_RESPONSE(L, 1);
	const char* data = luaL_checkstring(L, 2);
	onion_response_write0(response->response, data);
	return 0;
}

static int lua_onion_response_set_header(lua_State *L)
{
	lua_onion_response* response = CHECK_RESPONSE(L, 1);
	const char* key = luaL_checkstring(L, 2);
	const char* value = luaL_checkstring(L, 3);
	onion_response_set_header(response->response, key, value);
	return 0;
}

static int lua_onion_response_set_length(lua_State *L)
{
	lua_onion_response* response = CHECK_RESPONSE(L, 1);
	size_t length = luaL_checkinteger(L, 2);
	onion_response_set_length(response->response, length);
	return 0;
}

static int lua_onion_response_set_code(lua_State *L)
{
	lua_onion_response* response = CHECK_RESPONSE(L, 1);
	int code = luaL_checkinteger(L, 2);
	onion_response_set_code(response->response, code);
	return 0;
}

static int lua_onion_response_get_headers(lua_State *L)
{
	lua_onion_response* response = CHECK_RESPONSE(L, 1);
	lua_onion_dict* dict = create_new_onion_dict(L); // non-owning dict
	dict->dict = onion_response_get_headers(response->response);
	return 1;
}

static int lua_onion_response_add_cookie(lua_State *L)
{
	lua_onion_response* response = CHECK_RESPONSE(L, 1);
	const char* name = luaL_checkstring(L, 2);
	const char* value = luaL_checkstring(L, 3);
	time_t validity = luaL_checkinteger(L, 4);
	const char* path = luaL_checkstring(L, 5);
	const char* domain = luaL_checkstring(L, 6);
	int flags = luaL_checkinteger(L, 7);
	onion_response_add_cookie(response->response, name, value, validity, path, domain, flags);
	return 0;
}

static int lua_onion_response_write_html_safe(lua_State *L)
{
	lua_onion_response *response = CHECK_RESPONSE(L, 1);
	const char* data = luaL_checkstring(L, 2);
	onion_response_write_html_safe(response->response, data);
	return 0;
}

