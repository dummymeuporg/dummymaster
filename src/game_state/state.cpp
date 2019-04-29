#include "game_session.hpp"

#include "game_state/state.hpp"

GameState::State::State(::GameSession& session) :
    m_session(session)
{
}
