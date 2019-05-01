#pragma once

#include <cstdlib>
#include <memory>
#include <vector>

#include <boost/asio.hpp>

#include "game_state/state.hpp"

class GameServer;

class GameSession : public std::enable_shared_from_this<GameSession>
{
public:
    GameSession(boost::asio::ip::tcp::socket, GameServer&);
    void next();
    void start();

    GameServer& gameServer() {
        return m_gameServer;
    }

    boost::asio::ip::tcp::socket& socket() {
        return m_socket;
    }

    void changeState(GameState::State* state);

    std::vector<std::uint8_t> loadProfilePublicKey(const char* profile);

private:
    boost::asio::ip::tcp::socket m_socket;
    GameServer& m_gameServer;
    void _doReadHeader();
    void _doReadContent();

    std::uint16_t m_header;
    std::vector<uint8_t> m_payload;
    std::shared_ptr<GameState::State> m_state;
};
