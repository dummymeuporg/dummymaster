#define BOOST_LOG_DYN_LINK 1

#include "player_state/wrong_credentials_state.hpp"


PlayerState::WrongCredentialsState::WrongCredentialsState(
    ::PlayerSession& session,
    unsigned int attempts
) : PlayerState::State(session),
    m_attempts(attempts)
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
    // Again, check if password matches blablabla...
}
