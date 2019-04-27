#define BOOST_LOG_DYN_LINK 1
#include <string>

#include <boost/algorithm/hex.hpp>
#include <boost/log/trivial.hpp>

#include "players_server.hpp"
#include "player_session.hpp"
#include "crypto/sha512.hpp"
#include "player_state/initial_state.hpp"
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
    Account account(
        std::move(m_session.playersServer().fetchAccount(tagname))
    );

    if(::memcmp(account.password(), hash, SHA512_DIGEST_LENGTH)) {
        BOOST_LOG_TRIVIAL(debug) << "Wrong password.";
    } else {
        BOOST_LOG_TRIVIAL(debug) << "Correct password.";
    }
}
