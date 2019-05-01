#include <cstdlib>
#include <iostream>

#include <boost/asio.hpp>

#include "game_server.hpp"
#include "players_server.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " ACCOUNTS_DIR CONF_DIR"
            << std::endl;
        exit(EXIT_FAILURE);
    }

    boost::asio::io_service ioservice;
    PlayersServer server(ioservice, 33337, argv[1]);
    GameServer gameserver(ioservice, 33338, argv[2]);
    ioservice.run();

    return EXIT_SUCCESS;
}
