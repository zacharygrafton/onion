#include "types.h"

#include <onion/block.h>
#include <onion/low.h>
#include <lauxlib.h>

static lua_onion_block* create_new_onion_block(lua_State *L)
{
	lua_onion_block* block = lua_newuserdata(L, sizeof(lua_onion_block));
	luaL_getmetatable(L, "onion.Block");
	lua_setmetatable(L, -2);
	block->owner = false;
	return block;
}

static int lua_onion_block_new(lua_State *L)
{
	lua_onion_block* block = create_new_onion_block(L);
	block->block = onion_block_new();
	block->owner = true;
	return 1;
}

static int lua_onion_block_free(lua_State *L)
{
	lua_onion_block* block = CHECK_BLOCK(L, 1);
	if(block->owner == true)
		onion_block_free(block->block);
	return 0;
}

static int lua_onion_block_clear(lua_State *L)
{
	lua_onion_block* block = CHECK_BLOCK(L, 1);
	onion_block_clear(block->block);
	return 0;
}

static int lua_onion_block_size(lua_State *L)
{
	lua_onion_block* block = CHECK_BLOCK(L, 1);
	lua_pushinteger(L, onion_block_size(block->block));
	return 1;
}

static int lua_onion_block_data(lua_State *L)
{
	lua_onion_block* block = CHECK_BLOCK(L, 1);
	lua_pushstring(L, onion_block_data(block->block));
	return 1;
}

static int lua_onion_block_add(lua_State *L)
{
	lua_onion_block* block = CHECK_BLOCK(L, 1);
	size_t data_size = 0;
	const char* data = luaL_checklstring(L, 2, &data_size);
	onion_block_add_data(block->block, data, data_size);
	return 0;
}

static int lua_onion_block_add_block(lua_State *L)
{
	lua_onion_block* dest = CHECK_BLOCK(L, 1);
	lua_onion_block* src = CHECK_BLOCK(L, 2);
	onion_block_add_block(dest->block, src->block);
	return 0;
}

static int lua_onion_block_rewind(lua_State *L)
{
	lua_onion_block* block = CHECK_BLOCK(L, 1);
	off_t size = luaL_checkinteger(L, 2);
	onion_block_rewind(block->block, size);
	return 0;
}

static int lua_onion_block_min_maxsize(lua_State *L)
{
	lua_onion_block* block = CHECK_BLOCK(L, 1);
	int minsize = luaL_checkinteger(L, 2);
	onion_block_min_maxsize(block->block, minsize);
	return 0;
}

