#include <cstdlib>
#include <iostream>

#include <boost/asio.hpp>

#include "players_server.hpp"

int main(int argc, char* argv[])
{
    boost::asio::io_service ioservice;
    PlayersServer server(ioservice, 33337);
    ioservice.run();

    return EXIT_SUCCESS;
}
