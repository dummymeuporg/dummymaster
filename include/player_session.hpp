#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <boost/asio.hpp>

#include "player_state/state.hpp"


class PlayerSession : public std::enable_shared_from_this<PlayerSession>
{
public:
    PlayerSession(boost::asio::ip::tcp::socket);
    void start();

private:
    boost::asio::ip::tcp::socket m_socket;
    void _doReadHeader();
    void _doReadContent();

    std::uint16_t m_header;
    std::vector<std::uint8_t> m_payload;
    std::unique_ptr<PlayerState::State> m_state;
};