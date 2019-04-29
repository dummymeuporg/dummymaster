#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class GameServer {
public:
    GameServer(boost::asio::io_service&, unsigned short, const char*);

private:
    void _doAccept();
    boost::asio::ip::tcp::acceptor m_acceptor;
    fs::path m_confPath;

};
