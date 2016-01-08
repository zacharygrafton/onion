#include "types.h"

#include <lauxlib.h>

static lua_onion_request* create_new_onion_request(lua_State *L)
{
	lua_onion_request* request = (lua_onion_request*)lua_newuserdata(L, sizeof(lua_onion_request));
	luaL_getmetatable(L, "onion.Request");
	lua_setmetatable(L, -2);
	return request;
}

static int lua_onion_request_get_flags(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_pushinteger(L, onion_request_get_flags(request->request));
	return 1;
}

static int lua_onion_request_get_header(lua_State  *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	const char* header = luaL_checkstring(L, 2);
	lua_pushstring(L, onion_request_get_header(request->request, header));
	return 1;
}

static int lua_onion_request_get_path(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_pushstring(L, onion_request_get_path(request->request));
	return 1;
}

static int lua_onion_request_get_fullpath(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_pushstring(L, onion_request_get_fullpath(request->request));
	return 1;
}

static int lua_onion_request_advance_path(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	int addtopos = luaL_checkinteger(L, 2);
	onion_request_advance_path(request->request, addtopos);
	return 0;
}

static int lua_onion_request_get_query(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	const char* query = luaL_checkstring(L, 2);
	lua_pushstring(L, onion_request_get_query(request->request, query));
	return 1;
}

static int lua_onion_request_get_post(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	const char* key = luaL_checkstring(L, 2);
	lua_pushstring(L, onion_request_get_post(request->request, key));
	return 1;
}

static int lua_onion_request_get_session(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	const char* key = luaL_checkstring(L, 2);
	lua_pushstring(L, onion_request_get_session(request->request, key));
	return 1;
}

static int lua_onion_request_get_file(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	const char* key = luaL_checkstring(L, 2);
	lua_pushstring(L, onion_request_get_file(request->request, key));
	return 1;
}

static int lua_onion_request_get_header_dict(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_onion_dict* dict = create_new_onion_dict(L); // non-owning dict
	dict->dict = (onion_dict*)onion_request_get_header_dict(request->request);
	return 1;
}

static int lua_onion_request_get_query_dict(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_onion_dict* dict = create_new_onion_dict(L); // non-owning dict
	dict->dict = (onion_dict*)onion_request_get_query_dict(request->request);
	return 1;
}

static int lua_onion_request_get_post_dict(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_onion_dict* dict = create_new_onion_dict(L); // non-owning dict
	dict->dict = (onion_dict*)onion_request_get_post_dict(request->request);
	return 1;
}

static int lua_onion_request_get_file_dict(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_onion_dict* dict = create_new_onion_dict(L); // non-owning dict
	dict->dict = (onion_dict*)onion_request_get_file_dict(request->request);
	return 1;
}

static int lua_onion_request_get_session_dict(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_onion_dict* dict = create_new_onion_dict(L); // non-owning dict
	dict->dict = (onion_dict*)onion_request_get_session_dict(request->request);
	return 1;
}

static int lua_onion_request_get_cookies_dict(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_onion_dict* dict = create_new_onion_dict(L);
	dict->dict = (onion_dict*)onion_request_get_cookies_dict(request->request);
	return 1;
}

static int lua_onion_request_get_cookie(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	const char* key = luaL_checkstring(L, 2);
	lua_pushstring(L, onion_request_get_cookie(request->request, key));
	return 1;
}

static int lua_onion_request_get_language_code(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_pushstring(L, onion_request_get_language_code(request->request));
	return 1;
}

//FIXME:This will probably not work because of the implied free
static int lua_onion_request_get_data(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_onion_block* block = create_new_onion_block(L); // non-owning block
	block->block = (onion_block*)onion_request_get_data(request->request);
	return 1;
}

static int lua_onion_request_get_client_description(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_pushstring(L, onion_request_get_client_description(request->request));
	return 1;
}

static int lua_onion_request_is_secure(lua_State *L)
{
	lua_onion_request* request = CHECK_REQUEST(L, 1);
	lua_pushboolean(L, onion_request_is_secure(request->request));
	return 1;
}

