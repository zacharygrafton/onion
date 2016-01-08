#include "types.h"

#include <lauxlib.h>
#include <onion/low.h>

static lua_onion_dict* create_new_onion_dict(lua_State *L)
{
	lua_onion_dict* dict = (lua_onion_dict*)lua_newuserdata(L, sizeof(lua_onion_dict));
	luaL_getmetatable(L, "onion.Dict");
	lua_setmetatable(L, -2);
	dict->owner = false;
	return dict;
}

static int lua_onion_dict_new(lua_State *L)
{
	lua_onion_dict* dict = create_new_onion_dict(L);
	dict->dict = onion_dict_new();
	dict->owner = true;
	return 1;
}

static int lua_onion_dict_free(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	if(dict->owner == true)
		onion_dict_free(dict->dict);
	onion_low_free(dict);
	return 0;
}

static int lua_onion_dict_add(lua_State *L)
{
	int stacksize = lua_gettop(L);
	if(stacksize != 3 && stacksize != 4)
	{
		lua_pushliteral(L, "Incorrect number of arguments passed to add.");
		lua_error(L);
	}

	lua_onion_dict* dict = CHECK_DICT(L, 1);
	const char *key = luaL_checkstring(L, 2);
	const char *value = luaL_checkstring(L, 3);

	if(stacksize == 3)
		onion_dict_add(dict->dict, key, value, OD_DUP_ALL);
	else
	{
		int flags = luaL_checkinteger(L, 4);
		onion_dict_add(dict->dict, key, value, flags);
	}

	return 0;
}

static int lua_onion_dict_get(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	const char *key = luaL_checkstring(L, 2);
	lua_pushstring(L, onion_dict_get(dict->dict, key));
	return 1;
}

static int lua_onion_dict_remove(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	const char *key = luaL_checkstring(L, 2);
	onion_dict_remove(dict->dict, key);
	return 0;
}

static int lua_onion_dict_merge(lua_State *L)
{
	lua_onion_dict* dest = CHECK_DICT(L, 1);
	lua_onion_dict* src = CHECK_DICT(L, 2);
	onion_dict_merge(dest->dict, src->dict);
	return 0;
}

static int lua_onion_dict_count(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	lua_pushinteger(L, onion_dict_count(dict->dict));
	return 1;
}

static int lua_onion_dict_lock_read(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	onion_dict_lock_read(dict->dict);
	return 0;
}

static int lua_onion_dict_lock_write(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	onion_dict_lock_write(dict->dict);
	return 0;
}

static int lua_onion_dict_unlock(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	onion_dict_unlock(dict->dict);
	return 0;
}

static int lua_onion_dict_fromJSON(lua_State *L)
{
	const char* json = luaL_checkstring(L, 1);
	onion_dict* dict = onion_dict_from_json(json);

	lua_onion_dict* retval = create_new_onion_dict(L);
	retval->dict = dict;
	return 1;
}

static int lua_onion_dict_toJSON(lua_State *L)
{
	lua_onion_dict* dict = CHECK_DICT(L, 1);
	onion_block* block = onion_dict_to_json(dict->dict);
	lua_onion_block* retval = create_new_onion_block(L);
	retval->block = block;
	return 1;
}

