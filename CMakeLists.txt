cmake_minimum_required(VERSION 3.10.0)
project(dummymaster)
include_directories(include vendor/libdummy/include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
	-L${CMAKE_CURRENT_SOURCE_DIR}/vendor/libdummy/build \
	-lboost_filesystem -lboost_system -lboost_log -lpthread -lssl -lcrypto")


add_executable(dummymaster
	src/main.cpp
    src/account.cpp
    src/player_session.cpp
    src/players_server.cpp
    src/player_state/state.cpp
    src/player_state/initial_state.cpp
    src/player_state/right_credentials_state.cpp
    src/player_state/wrong_credentials_state.cpp
    src/game_session.cpp
    src/game_server.cpp
    src/game_state/profile_exists_state.cpp
    src/game_state/initial_state.cpp
    src/game_state/state.cpp
)

target_link_libraries(dummymaster dummy)
