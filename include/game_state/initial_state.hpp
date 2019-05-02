#pragma once

#include "game_state/state.hpp"

namespace GameState {
    class InitialState : public State
    {
    public:
        static const std::uint8_t PROFILE_NOT_FOUND = 0;
        static const std::uint8_t PROFILE_FOUND = 1;
        static const std::uint8_t PROFILE_ALREADY_CONNECTED = 2;
        InitialState(::GameSession&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
