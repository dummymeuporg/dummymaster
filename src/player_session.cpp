#define BOOST_LOG_DYN_LINK 1

#include <iostream>

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "player_state/initial_state.hpp"

#include "players_server.hpp"

#include "player_session.hpp"

PlayerSession::PlayerSession(boost::asio::ip::tcp::socket s,
                             PlayersServer& playersServer)
    : m_socket(std::move(s)),
      m_playersServer(playersServer),
      m_state(std::make_shared<PlayerState::InitialState>(*this))
{
}

void PlayerSession::start()
{
    BOOST_LOG_TRIVIAL(debug) << "Session started.";
    _doReadHeader();
}

void PlayerSession::next()
{
    BOOST_LOG_TRIVIAL(debug) << "Read next payload.";
    _doReadHeader();
}

void PlayerSession::_doReadHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(&m_header, sizeof(std::uint16_t)),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                m_payload.resize(m_header);
                _doReadContent();
            }
        }
    );
}

void PlayerSession::_doReadContent()
{
    auto self(shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(m_payload, m_header),
        [this, self](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                BOOST_LOG_TRIVIAL(debug) << "Read " << lenght << " bytes.";
                m_state->onRead(m_payload);
            }
        }
    );
}

void PlayerSession::changeState(std::shared_ptr<PlayerState::State> state) {
    std::cerr << "Change state." << std::endl;
    m_state = state;
}
