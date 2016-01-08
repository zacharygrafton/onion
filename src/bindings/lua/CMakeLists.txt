include_directories(${LUA_INCLUDE_DIRS})

add_library(onion_lua SHARED
	main.c
)
set_target_properties(onion_lua PROPERTIES
	PREFIX ""
	OUTPUT_NAME "onion"
)

target_link_libraries(onion_lua onion)

install(TARGETS onion_lua DESTINATION ${LUA_BINDINGS_INSTALL_DIR})

