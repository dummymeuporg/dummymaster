#define BOOST_LOG_DYN_LINK 1

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/log/trivial.hpp>

#include "crypto/sha512.hpp"

#include "account.hpp"
#include "players_server.hpp"
#include "player_session.hpp"

PlayersServer::PlayersServer(boost::asio::io_service& ioService,
                             unsigned short port,
                             const char* accountsPath)
    : m_acceptor(ioService,
                 boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                port)),
    m_accountsPath(std::move(accountsPath))
{
    _doAccept();
}


void PlayersServer::_doAccept()
{
    m_acceptor.async_accept(
        [this](boost::system::error_code ec,
               boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<PlayerSession>(std::move(socket),
                                                *this)->start();
            }
            _doAccept();
        }
    );
}

Account PlayersServer::fetchAccount(const std::string& tagname) const {
    fs::path pwdFile{m_accountsPath / tagname / "password"};

	BOOST_LOG_TRIVIAL(debug) << "Try to fetch account " << tagname;

    if (!fs::exists(pwdFile)) {
		BOOST_LOG_TRIVIAL(debug) << "password file not found.";
        throw AccountNotFound();
    }

	Account account(tagname);

    // Read the password file.
    std::ifstream file(pwdFile.string());

	if (!file.is_open()) {
		throw AccountNotFound();
	}

	file.read(reinterpret_cast<char*>(account.password()),
			  SHA512_DIGEST_LENGTH);

	return account;
}
