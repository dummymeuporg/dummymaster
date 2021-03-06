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

    const std::string& serverName() const {
        return m_serverName;
    }

    std::uint16_t connectedPlayers() const {
        return m_connectedPlayers;
    }

    std::uint16_t maxSlots() const {
        return m_maxSlots;
    }

    GameSession& setServerName(const std::string& serverName);
    GameSession& setConnectedPlayers(std::uint16_t connectedPlayers);
    GameSession& setMaxSlots(std::uint16_t maxSlots);

private:
    boost::asio::ip::tcp::socket m_socket;
    GameServer& m_gameServer;
    void _doReadHeader();
    void _doReadContent();

    std::uint16_t m_header;
    std::vector<uint8_t> m_payload;
    std::shared_ptr<GameState::State> m_state;
    std::string m_serverName;
    std::uint16_t m_connectedPlayers;
    std::uint16_t m_maxSlots;
};
