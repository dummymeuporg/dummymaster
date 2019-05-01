#define BOOST_LOG_DYN_LINK 1
#include <string>

#include <boost/log/trivial.hpp>

#include "game_server.hpp"
#include "game_session.hpp"
#include "game_state/initial_state.hpp"


GameState::InitialState::InitialState(::GameSession& session)
    : GameState::State(session)
{
}

void GameState::InitialState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    const std::string& serverName(
        reinterpret_cast<const char*>(buffer.data()));
    BOOST_LOG_TRIVIAL(debug) << "Hello, " << serverName;

    // Check if the server exists.
}
