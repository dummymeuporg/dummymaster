cmake_minimum_required(VERSION 3.10.0)
project(dummymaster)
include_directories(include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem -lboost_system -lboost_log -lpthread")
add_executable(dummymaster
	src/main.cpp
    src/player_session.cpp
    src/players_server.cpp
)
