cmake_minimum_required(VERSION 3.10.0)
project(dummymaster)
include_directories(include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
	-L${CMAKE_CURRENT_SOURCE_DIR}/vendor/libdummy/build -ldummy \
	-lboost_filesystem -lboost_system -lboost_log -lpthread")
add_executable(dummymaster
	src/main.cpp
    src/player_session.cpp
    src/players_server.cpp
    src/player_state/state.cpp
    src/player_state/initial_state.cpp
)
