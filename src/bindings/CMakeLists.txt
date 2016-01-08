if (${ONION_USE_BINDINGS_CPP})
	add_subdirectory(cpp)
endif (${ONION_USE_BINDINGS_CPP})

if (${ONION_USE_BINDINGS_LUA})
	add_subdirectory(lua)
endif (${ONION_USE_BINDINGS_LUA})

