#define BOOST_LOG_DYN_LINK 1
#include <string>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

#include "game_server.hpp"
#include "game_session.hpp"
#include "game_state/initial_state.hpp"

namespace fs = boost::filesystem;

GameState::InitialState::InitialState(::GameSession& session)
    : GameState::State(session)
{
}

void GameState::InitialState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    const std::string& serverName(
        reinterpret_cast<const char*>(buffer.data()));
    GameState::State* nextState = nullptr;
    BOOST_LOG_TRIVIAL(debug) << "Hello, " << serverName;

    std::vector<std::uint8_t> answer(
        sizeof(std::uint16_t) + sizeof(std::uint8_t)
    );

    // We only send back one byte.
    *(reinterpret_cast<std::uint16_t*>(answer.data())) = 
        sizeof(std::uint8_t);

    // Check if the server exists.
    if (fs::exists(fs::path(
            m_session.gameServer().confPath() / "game_servers" / serverName)))
    {
        BOOST_LOG_TRIVIAL(debug) << "Recognized game server.";
        // Send back "True" to the server. Change state.
        *(answer.data() + sizeof(std::uint16_t)) = 1;
        nextState = nullptr;
    }
    else
    {
        // Send back "False" to the server. Close connection?
        *(answer.data() + sizeof(std::uint16_t)) = 0;
    }

    boost::asio::async_write(
        m_session.socket(),
        boost::asio::buffer(answer, answer.size()),
        [this](boost::system::error_code ec, std::size_t lenght) {
            if (!ec) {
            }
        }
    );
}
