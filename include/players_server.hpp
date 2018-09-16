#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>


class PlayersServer
{
public:
    PlayersServer(boost::asio::io_service&, unsigned short);
    void _doAccept();

private:
    boost::asio::ip::tcp::acceptor m_acceptor;

};
