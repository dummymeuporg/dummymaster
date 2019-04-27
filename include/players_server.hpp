#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class PlayersServer
{
public:
    PlayersServer(boost::asio::io_service&, unsigned short, const char*);

private:
    void _doAccept();
    bool _accountExists(const std::string&) const;
    boost::asio::ip::tcp::acceptor m_acceptor;
    fs::path m_accountsPath;
};
