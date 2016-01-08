#include "types.h"

#include <lauxlib.h>
#include <onion/low.h>

#include <stdio.h>

static onion_connection_status callback(void *data, onion_request* request, onion_response* response)
{
	callback_data* c = (callback_data*)data;

	lua_rawgeti(c->L, LUA_REGISTRYINDEX, c->ref);

	lua_onion_request* req = create_new_onion_request(c->L);
	lua_onion_response* res = create_new_onion_response(c->L);

	req->request = request;
	res->response = response;

	lua_pcall(c->L, 2, 1, 0);
	int retval = luaL_checkinteger(c->L, -1);
	lua_pop(c->L, 1);
	return retval;
}

static void callback_free(void* data)
{
	callback_data* d = (callback_data*)data;
	luaL_unref(d->L, LUA_REGISTRYINDEX, d->ref);

	onion_low_free(d);
}

static lua_onion_handler* create_new_onion_handler(lua_State *L)
{
	lua_onion_handler* handler = (lua_onion_handler*)lua_newuserdata(L, sizeof(lua_onion_handler));
	luaL_getmetatable(L, "onion.Handler");
	lua_setmetatable(L, -2);
	handler->owner = false;
	return handler;
}

static int lua_onion_handler_new(lua_State *L)
{
	callback_data* data = onion_low_malloc(sizeof(callback_data));
	data->L = L;
	data->ref = luaL_ref(L, LUA_REGISTRYINDEX); // get a reference to the callback

	lua_onion_handler* handler = create_new_onion_handler(L);
	handler->owner = true;
	handler->handler = onion_handler_new(callback, data, callback_free);
	return 1;
}

static int lua_onion_handler_free(lua_State *L)
{
	lua_onion_handler* handler = CHECK_HANDLER(L, 1);
	if(handler->owner == true)
		onion_handler_free(handler->handler);
	onion_low_free(handler);
	return 0;
}

static int lua_onion_handler_add(lua_State *L)
{
	lua_onion_handler* parent = CHECK_HANDLER(L, 1);
	lua_onion_handler* child = CHECK_HANDLER(L, 2);

	onion_handler_add(parent->handler, child->handler);
	child->owner = false;
	return 0;
}

