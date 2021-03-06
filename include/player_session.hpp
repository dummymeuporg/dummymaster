#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <boost/asio.hpp>

#include "player_state/state.hpp"

class PlayersServer;

class PlayerSession : public std::enable_shared_from_this<PlayerSession>
{
public:
    PlayerSession(boost::asio::ip::tcp::socket, PlayersServer&);
    void next();
    void start();

    boost::asio::ip::tcp::socket& socket() {
        return m_socket;
    }

    PlayersServer& playersServer() {
        return m_playersServer;
    }

    void changeState(std::shared_ptr<PlayerState::State> state);

private:
    boost::asio::ip::tcp::socket m_socket;
    PlayersServer& m_playersServer;
    void _doReadHeader();
    void _doReadContent();

    std::uint16_t m_header;
    std::vector<std::uint8_t> m_payload;
    std::shared_ptr<PlayerState::State> m_state;
};
