#pragma once

#include "game_state/state.hpp"

namespace GameState {
    class InitialState : public State
    {
    public:
        InitialState(::GameSession&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
