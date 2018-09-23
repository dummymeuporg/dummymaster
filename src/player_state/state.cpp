#include "player_session.hpp"

#include "player_state/state.hpp"


PlayerState::State::State(::PlayerSession& session) :
    m_session(session)
{
}

