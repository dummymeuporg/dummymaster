#define BOOST_LOG_DYN_LINK 1

#include "player_state/right_credentials_state.hpp"


PlayerState::RightCredentialsState::RightCredentialsState(
    ::PlayerSession& session,
    ::Account account
) : PlayerState::State(session)
{
    // Generate some token?
    // Send list of connected game servers?
}

void PlayerState::RightCredentialsState::onRead(
        const std::vector<std::uint8_t>&buffer)
{

}
