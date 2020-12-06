cmake_minimum_required (VERSION 2.6)
project (lua-windcon)

# Lua
find_package (Lua REQUIRED)

# Our Module
add_library( windcon MODULE windcon.c )
target_link_libraries ( windcon ${LUA_LIBRARIES} )
target_include_directories( windcon PRIVATE ${LUA_INCLUDE_DIR} )
set_target_properties( windcon PROPERTIES PREFIX "" )

if (UNIX OR CMAKE_HOST_UNIX)
add_library( windcon_s STATIC windcon.c )
target_link_libraries ( windcon_s ${LUA_LIBRARIES} )
target_include_directories ( windcon_s PRIVATE ${LUA_INCLUDE_DIR} )
set_target_properties ( windcon_s PROPERTIES OUTPUT_NAME windcon )
endif()

# LUA is set by Luarocks
if (LUA)
  SET(INSTALL_LIB_DIR ${LIBDIR})
elseif (UNIX OR APPLE)
  set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}")
endif()

if (INSTALL_LIB_DIR)
  install(TARGETS windcon ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" LIBRARY DESTINATION "${INSTALL_LIB_DIR}")
endif ()
