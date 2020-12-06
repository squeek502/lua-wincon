cmake_minimum_required (VERSION 2.6)
project (lua-wincon)

# Lua
find_package (Lua REQUIRED)

# Our Module
add_library( wincon MODULE wincon.c )
target_link_libraries ( wincon ${LUA_LIBRARIES} )
target_include_directories( wincon PRIVATE ${LUA_INCLUDE_DIR} )