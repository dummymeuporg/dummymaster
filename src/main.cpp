#include <cstdlib>
#include <iostream>

#include <boost/asio.hpp>

#include "players_server.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " ACCOUNTS_DIR CONF_DIR"
            << std::endl;
        exit(EXIT_FAILURE);
    }

    boost::asio::io_service ioservice;
    PlayersServer server(ioservice, 33337, argv[1]);
    //GameServers gameservers(ioservice, 33338);
    ioservice.run();

    return EXIT_SUCCESS;
}
