#define BOOST_LOG_DYN_LINK 1

#include "player_state/wrong_credentials_state.hpp"


PlayerState::WrongCredentialsState::WrongCredentialsState(
    ::PlayerSession& session
) : PlayerState::State(session)
{
    // Send response to server.
    // Disconnect?
    // Log something?
    // Close the connection? Or get back at the initial state with an
    // attempt counter?
}

void PlayerState::WrongCredentialsState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    // This should not be called, I think.
}
