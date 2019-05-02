#include <iostream>
#include <string>

#include "game_session.hpp"
#include "game_state/profile_exists_state.hpp"

GameState::ProfileExistsState::ProfileExistsState(::GameSession& session)
    : GameState::State(session)
{
}

void
GameState::ProfileExistsState::onRead(const std::vector<std::uint8_t>& buffer)
{
    // Packet should have :
    //     - connected players (std::uint16_t)
    //     - max slots (std::uint16_t)
    
    if (buffer.size() != sizeof(std::uint16_t) * 2)
    {
        // TODO: handle error. This is a malformed packet.
        return;
    }

    m_session.setConnectedPlayers(
        *(reinterpret_cast<const std::uint16_t*>(buffer.data()))
    );

    std::cerr << "Connected players: " << m_session.connectedPlayers()
        << std::endl;

    m_session.setMaxSlots(
        *(reinterpret_cast<const std::uint16_t*>(buffer.data()) + 1)
    );

    std::cerr << "Max slots: " << m_session.maxSlots() << std::endl;
}
