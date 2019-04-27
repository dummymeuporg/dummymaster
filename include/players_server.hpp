#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>

#include "account.hpp"

namespace fs = boost::filesystem;

class PlayersServer
{
public:
    PlayersServer(boost::asio::io_service&, unsigned short, const char*);
    bool accountExists(const std::string&) const;
    Account fetchAccount(const std::string&) const;

private:
    void _doAccept();
    boost::asio::ip::tcp::acceptor m_acceptor;
    fs::path m_accountsPath;
};
