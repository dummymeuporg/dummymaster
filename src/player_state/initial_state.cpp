#define BOOST_LOG_DYN_LINK 1
#include <string>
#include <memory>

#include <boost/algorithm/hex.hpp>
#include <boost/log/trivial.hpp>

#include "players_server.hpp"
#include "player_session.hpp"
#include "crypto/sha512.hpp"

#include "player_state/initial_state.hpp"
#include "player_state/right_credentials_state.hpp"
#include "player_state/wrong_credentials_state.hpp"

#include "utils.hpp"

PlayerState::InitialState::InitialState(::PlayerSession& session)
    : PlayerState::State(session)
{

}

void PlayerState::InitialState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    if (buffer.size() < SHA512_DIGEST_LENGTH)
    {
        // XXX: Throw an error somehow
        return;
    }

    std::string tagname(reinterpret_cast<const char*>(buffer.data()),
                        size_t(buffer.size() - SHA512_DIGEST_LENGTH));

    // Pass the tagname to uppercase
    std::transform(tagname.begin(), tagname.end(), tagname.begin(),
                   [](unsigned char c) {
                        return std::isalpha(c) ? std::toupper(c) : c; 
                    }
    );

    const std::uint8_t* hash = buffer.data()
        + buffer.size()
        - SHA512_DIGEST_LENGTH;
    BOOST_LOG_TRIVIAL(debug) << "Tagname is: " << tagname;
    ::hexdump(hash, SHA512_DIGEST_LENGTH);

    // TODO: Check if the username exists!
    std::shared_ptr<Account> account(
        std::move(m_session.playersServer().fetchAccount(tagname))
    );

    hexdump(account->password(), SHA512_DIGEST_LENGTH);

    if(::memcmp(account->password(), hash, SHA512_DIGEST_LENGTH)) {
        BOOST_LOG_TRIVIAL(debug) << "Wrong password.";
        _sendResult(0, account);
    } else {
        BOOST_LOG_TRIVIAL(debug) << "Correct password.";
        _sendResult(1, account);
    }
}

void
PlayerState::InitialState::_sendResult(std::uint8_t result,
                                       std::shared_ptr<Account> account)
{
    auto self(m_session.shared_from_this());

    std::vector<std::uint8_t> packet(
        sizeof(std::uint16_t) + sizeof(std::uint8_t)
    );
    *(reinterpret_cast<std::uint16_t*>(packet.data())) = 
        sizeof(std::uint8_t);
    *(packet.data() + sizeof(std::uint16_t)) = result;

    boost::asio::async_write(
        m_session.socket(),
        boost::asio::buffer(packet, packet.size()),
        [this,
         self,
         result,
         account
        ](boost::system::error_code ec, std::size_t length)
        {
            if (!ec) {
                if (result == 1) {
                /*
                    m_session.changeState(
                        new PlayerState::RightCredentialsState(
                            m_session,
                            account
                        )
                    );
                    */
                } else {
                    m_session.changeState(
                        new PlayerState::WrongCredentialsState(
                            m_session, 
                            1 /* attempts */
                        )
                    );
                }

                m_session.next(); /* read next packet */
            }
        }
    );
}
