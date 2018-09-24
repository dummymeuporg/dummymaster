#include "player_state/initial_state.hpp"

PlayerState::InitialState::InitialState(::PlayerSession& session)
    : PlayerState::State(session)
{

}

void PlayerState::InitialState::onRead(
    const std::vector<std::uint8_t>& buffer)
{

}
