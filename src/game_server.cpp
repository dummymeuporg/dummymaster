#define BOOST_LOG_DYN_LINK 1

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

#include "game_server.hpp"
#include "game_session.hpp"

namespace fs = boost::filesystem;

GameServer::GameServer(boost::asio::io_service& ioService,
                       unsigned short port,
                       const char* confPath)
    : m_acceptor(ioService,
                 boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                port)),
    m_confPath(confPath),
    m_rsaKeyPair(fs::path(m_confPath / ".conf" / "pub.pem").string(),
                 fs::path(m_confPath / ".conf" / "priv.pem").string())
{
    BOOST_LOG_TRIVIAL(debug) << "Game server started. Accept connections.";
    _doAccept();
}

GameServer&
GameServer::connectServer(std::shared_ptr<GameSession> gameSession)
{
    const std::string& serverName(gameSession->serverName());
    if (!isServerConnected(serverName)) {
        m_connectedGameServers[serverName] = gameSession;
    }
    return *this;
}

void GameServer::_doAccept() {
    m_acceptor.async_accept(
        [this](boost::system::error_code ec,
               boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                BOOST_LOG_TRIVIAL(debug) << "Game server create session.";
                std::make_shared<GameSession>(std::move(socket),
                                              *this)->start();
            }
            _doAccept();
        }
    );
}
