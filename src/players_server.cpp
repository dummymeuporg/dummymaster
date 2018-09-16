#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "players_server.hpp"
#include "player_session.hpp"

PlayersServer::PlayersServer(boost::asio::io_service& ioService,
                             unsigned short port)
    : m_acceptor(ioService,
                 boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                port))
{
    _doAccept();
}


void PlayersServer::_doAccept()
{
    m_acceptor.async_accept(
        [this](boost::system::error_code ec,
               boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<PlayerSession>(std::move(socket))->start();
            }
            _doAccept();
        }
    );
}
