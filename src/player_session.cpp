#define BOOST_LOG_DYN_LINK 1
#include "player_session.hpp"

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

PlayerSession::PlayerSession(boost::asio::ip::tcp::socket s)
    : m_socket(std::move(s))
{
}

void PlayerSession::start()
{
    _doReadHeader();
}

void PlayerSession::_doReadHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(&m_header, sizeof(std::uint16_t)),
        [this, self](boost::system::error_code ec, std::size_t lenght)
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
                _doReadHeader();
            }
        }
    );
}
