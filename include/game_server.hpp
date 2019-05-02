#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>

#include "crypto/rsa_keypair.hpp"

#include "game_session.hpp"

namespace fs = boost::filesystem;

class GameServer {
public:
    GameServer(boost::asio::io_service&, unsigned short, const char*);

    const Dummy::Crypto::RSAKeyPair& rsaKeyPair() const {
        return m_rsaKeyPair;
    }

    const fs::path& confPath() const {
        return m_confPath;
    }

    const std::map<std::string, std::shared_ptr<GameSession>>&
    connectedGameServers() const {
        return m_connectedGameServers;
    }

    bool isServerConnected(const std::string& serverName) const {
        return m_connectedGameServers.find(serverName) !=
            m_connectedGameServers.end();
    }

    GameServer& connectServer(std::shared_ptr<GameSession> gameSession); 

private:
    void _doAccept();
    boost::asio::ip::tcp::acceptor m_acceptor;
    fs::path m_confPath;
    Dummy::Crypto::RSAKeyPair m_rsaKeyPair;
    std::map<std::string, std::shared_ptr<GameSession>> m_connectedGameServers;

};
