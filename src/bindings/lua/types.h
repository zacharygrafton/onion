#ifndef LUA_ONION_TYPES_H
#define LUA_ONION_TYPES_H

#include <lua.h>
#include <stdbool.h>
#include <onion/onion.h>
#include <onion/dict.h>

typedef struct callback_data_t
{
	int ref;
	lua_State *L;
} callback_data;

typedef struct lua_onion_t
{
	onion* o;
} lua_onion;

typedef struct lua_onion_url_t
{
	bool owner;
	onion_url* url;
} lua_onion_url;

typedef struct lua_onion_dict_t
{
	bool owner;
	onion_dict* dict;
} lua_onion_dict;

typedef struct lua_onion_block_t
{
	bool owner;
	onion_block* block;
} lua_onion_block;

typedef struct lua_onion_handler_t
{
	bool owner;
	onion_handler* handler;
} lua_onion_handler;

typedef struct lua_onion_request_t
{
	onion_request* request;
} lua_onion_request;

typedef struct lua_onion_response_t
{
	onion_response* response;
} lua_onion_response;

typedef struct lua_onion_sessions_t
{
	onion_sessions* sessions;
} lua_onion_sessions;

static int lua_onion_new(lua_State *L);
static int lua_onion_free(lua_State *L);
static int lua_onion_listen(lua_State *L);
static int lua_onion_listen_stop(lua_State *L);
static int lua_onion_set_root_handler(lua_State *L);
static int lua_onion_root_url(lua_State *L);
static int lua_onion_set_session_backend(lua_State *L);

static int lua_onion_url_new(lua_State *L);
static int lua_onion_url_free(lua_State *L);
static int lua_onion_url_add(lua_State *L);
static int lua_onion_url_add_static(lua_State *L);
static int lua_onion_url_to_handler(lua_State *L);
static int lua_onion_url_add_url(lua_State *L);

static int lua_onion_dict_new(lua_State *L);
static int lua_onion_dict_fromJSON(lua_State *L);
static int lua_onion_dict_free(lua_State *L);
static int lua_onion_dict_add(lua_State *L);
static int lua_onion_dict_get(lua_State *L);
static int lua_onion_dict_remove(lua_State *L);
static int lua_onion_dict_merge(lua_State *L);
static int lua_onion_dict_count(lua_State *L);
static int lua_onion_dict_lock_read(lua_State *L);
static int lua_onion_dict_lock_write(lua_State *L);
static int lua_onion_dict_unlock(lua_State *L);
static int lua_onion_dict_toJSON(lua_State *L);

static int lua_onion_block_new(lua_State *L);
static int lua_onion_block_free(lua_State *L);
static int lua_onion_block_clear(lua_State *L);
static int lua_onion_block_size(lua_State *L);
static int lua_onion_block_data(lua_State *L);
static int lua_onion_block_add(lua_State *L);
static int lua_onion_block_add_block(lua_State *L);
static int lua_onion_block_rewind(lua_State *L);
static int lua_onion_block_min_maxsize(lua_State *L);

static int lua_onion_response_set_header(lua_State *L);
static int lua_onion_response_set_length(lua_State *L);
static int lua_onion_response_set_code(lua_State *L);
static int lua_onion_response_get_headers(lua_State *L);
static int lua_onion_response_add_cookie(lua_State *L);
static int lua_onion_response_write(lua_State *L);
static int lua_onion_response_write_html_safe(lua_State *L);

static int lua_onion_request_get_flags(lua_State *L);
static int lua_onion_request_get_data(lua_State *L);
static int lua_onion_request_get_header(lua_State *L);
static int lua_onion_request_get_path(lua_State *L);
static int lua_onion_request_get_fullpath(lua_State *L);
static int lua_onion_request_advance_path(lua_State *L);
static int lua_onion_request_get_query(lua_State *L);
static int lua_onion_request_get_post(lua_State *L);
static int lua_onion_request_get_file(lua_State *L);
static int lua_onion_request_get_session(lua_State *L);
static int lua_onion_request_get_header_dict(lua_State *L);
static int lua_onion_request_get_query_dict(lua_State *L);
static int lua_onion_request_get_post_dict(lua_State *L);
static int lua_onion_request_get_file_dict(lua_State *L);
static int lua_onion_request_get_session_dict(lua_State *L);
static int lua_onion_request_get_cookies_dict(lua_State *L);
static int lua_onion_request_get_cookie(lua_State *L);
static int lua_onion_request_get_language_code(lua_State *L);
static int lua_onion_request_get_client_description(lua_State *L);
static int lua_onion_request_is_secure(lua_State *L);

static int lua_onion_handler_new(lua_State *L);
static int lua_onion_handler_free(lua_State *L);
static int lua_onion_handler_add(lua_State *L);

#ifdef HAVE_REDIS
static int lua_onion_redis_sessions_new(lua_State *L);
#endif

#ifdef HAVE_SQLITE3
static int lua_onion_sqlite3_sessions_new(lua_State *L);
#endif

#define CHECK_ONION(state, index) \
	(lua_onion*)luaL_checkudata(state, index, "onion.Onion")

#define CHECK_BLOCK(state, index) \
	(lua_onion_block*)luaL_checkudata(state, index, "onion.Block")

#define CHECK_DICT(state, index) \
	(lua_onion_dict*)luaL_checkudata(state, index, "onion.Dict")

#define CHECK_URL(state, index) \
	(lua_onion_url*)luaL_checkudata(state, index, "onion.Url")

#define CHECK_REQUEST(state, index) \
	(lua_onion_request*)luaL_checkudata(state, index, "onion.Request")

#define CHECK_RESPONSE(state, index) \
	(lua_onion_response*)luaL_checkudata(state, index, "onion.Response")

#define CHECK_HANDLER(state, index) \
	(lua_onion_handler*)luaL_checkudata(state, index, "onion.Handler")

#define CHECK_SESSIONS(state, index) \
	(lua_onion_sessions*)luaL_checkudata(state, index, "onion.Sessions")

static lua_onion* create_new_onion(lua_State *L);
static lua_onion_block* create_new_onion_block(lua_State *L);
static lua_onion_dict* create_new_onion_dict(lua_State *L);
static lua_onion_request* create_new_onion_request(lua_State *L);
static lua_onion_response* create_new_onion_response(lua_State *L);
static lua_onion_handler* create_new_onion_handler(lua_State *L);
static lua_onion_url* create_new_onion_url(lua_State *L);
static lua_onion_sessions* create_new_onion_sessions(lua_State *L);

#include "onion.h"
#include "url.h"
#include "response.h"
#include "request.h"
#include "block.h"
#include "dict.h"
#include "handler.h"
#include "sessions.h"

#endif

