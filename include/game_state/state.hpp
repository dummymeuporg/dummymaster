#pragma once

#include <cstdint>
#include <vector>

class GameSession;

namespace GameState {
    class State {
    public:
        State(::GameSession&);
        virtual void onRead(const std::vector<std::uint8_t>&) = 0;
    protected:
        ::GameSession& m_session;
    };
}
