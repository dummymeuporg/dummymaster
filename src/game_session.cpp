#define BOOST_LOG_DYN_LINK 1

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "crypto/rsa_keypair.hpp"

#include "game_state/initial_state.hpp"

#include "game_server.hpp"

#include "game_session.hpp"

GameSession::GameSession(boost::asio::ip::tcp::socket s,
                         GameServer& gameServer)
    : m_socket(std::move(s)),
      m_gameServer(gameServer),
      m_state(new GameState::InitialState(*this))
{

}

void GameSession::start()
{
    BOOST_LOG_TRIVIAL(debug) << "Game Session started.";
    _doReadHeader();
}

void GameSession::next() {
    BOOST_LOG_TRIVIAL(debug) << "Read next payload.";
    _doReadHeader();
}

void GameSession::_doReadHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(&m_header, sizeof(std::uint16_t)),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                m_payload.resize(m_header);
                _doReadContent();
            }
        }
    );
}

void GameSession::_doReadContent()
{
    auto self(shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(m_payload, m_header),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                BOOST_LOG_TRIVIAL(debug) << "Read " << length << " bytes.";
                m_state->onRead(m_payload);
            }
        }
    );
}

void GameSession::changeState(GameState::State* state) {
    m_state.reset(state);
}

GameSession&
GameSession::setServerName(const std::string& serverName)
{
    m_serverName = serverName;
    return *this;
}

std::vector<std::uint8_t>
GameSession::loadProfilePublicKey(const char* profile) {

    size_t keySize = 0;
    std::vector<std::uint8_t> rawKey;

    ::FILE *fpub = ::fopen(
        fs::path(m_gameServer.confPath() /
            "game_servers" / profile / "pub.pem").string().c_str(), "rb");
    if (nullptr == fpub) {
        throw Dummy::Crypto::PEMFileError();
    }

    ::EVP_PKEY* profilePubKey = ::PEM_read_PUBKEY(fpub, NULL, NULL, NULL);
    if (nullptr == profilePubKey) {
        ::fclose(fpub);
        throw Dummy::Crypto::KeyLoadingError();
    }

    // From now on, we do not need the file descriptor anymore.
    ::fclose(fpub);

    ::EVP_PKEY_get_raw_public_key(profilePubKey, NULL, &keySize);

    if(0 == keySize) {
        ::EVP_PKEY_free(profilePubKey);
        throw Dummy::Crypto::KeyLoadingError();
    }

    rawKey.resize(keySize);

    ::EVP_PKEY_get_raw_public_key(profilePubKey, rawKey.data(), &keySize);

    BOOST_LOG_TRIVIAL(debug) << "Key size: " << keySize << " bytes.";

    return rawKey;

}
