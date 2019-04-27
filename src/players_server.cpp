#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "players_server.hpp"
#include "player_session.hpp"

PlayersServer::PlayersServer(boost::asio::io_service& ioService,
                             unsigned short port,
                             const char* accountsPath)
    : m_acceptor(ioService,
                 boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                port)),
    m_accountsPath(std::move(accountsPath))
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

bool PlayersServer::_accountExists(const std::string& tagName) const {
    fs::path playerDir{m_accountsPath / tagName};
}
