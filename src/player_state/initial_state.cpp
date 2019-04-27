#define BOOST_LOG_DYN_LINK 1
#include <string>

#include <boost/log/trivial.hpp>

#include "crypto/sha512.hpp"
#include "player_state/initial_state.hpp"

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
    const std::uint8_t* hash = buffer.data()
        + buffer.size()
        - SHA512_DIGEST_LENGTH;
    BOOST_LOG_TRIVIAL(debug) << "Tagname is: " << tagname;

    // TODO: Check if the username exists!

}
