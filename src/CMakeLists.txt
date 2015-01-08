cmake_minimum_required (VERSION 2.6)
include_directories(${X_SERVER_SOURCE_DIR}/lib)
include_directories(${X_SERVER_SOURCE_DIR}/src)
option (WITH_DEBUG "Compile a debug server" OFF)
if (WITH_DEBUG)
  set(CMAKE_CXX_FLAGS "-g -Wall -Werror -pthread")
  set(CMAKE_C_FLAGS "-g -Wall -Werror -pthread")
else (WITH_DEBUG)
  set(CMAKE_CXX_FLAGS "-pthread")
  set(CMAKE_C_FLAGS "-pthread")
endif (WITH_DEBUG)
add_executable(        x-server
                       x_network.cc
                       x_idstate.cc
                       x_auth.cc
                       x_thd.cc
                       x_com.cc
                       x_server.cc
                       )
install(TARGETS x-server DESTINATION ${CMAKE_INSTALL_PREFIX})

