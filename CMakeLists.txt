cmake_minimum_required (VERSION 2.6)
project (lua-wincon)

# Lua
find_package (Lua REQUIRED)

# Our Module
add_library( wincon MODULE wincon.c )
target_link_libraries ( wincon ${LUA_LIBRARIES} )
target_include_directories( wincon PRIVATE ${LUA_INCLUDE_DIR} )
set_target_properties( wincon PROPERTIES PREFIX "" )

if (UNIX OR CMAKE_HOST_UNIX)
add_library( wincon_s STATIC wincon.c )
target_link_libraries ( wincon_s ${LUA_LIBRARIES} )
target_include_directories ( wincon_s PRIVATE ${LUA_INCLUDE_DIR} )
set_target_properties ( wincon_s PROPERTIES OUTPUT_NAME wincon )
endif()

# LUA is set by Luarocks
if (LUA)
  SET(INSTALL_LIB_DIR ${LIBDIR})
elseif (UNIX OR APPLE)
  set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}")
endif()

if (INSTALL_LIB_DIR)
  install(TARGETS wincon ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
endif ()
