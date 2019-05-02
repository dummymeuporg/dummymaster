#pragma once

#include "game_state/state.hpp"

namespace GameState {
    class ProfileExistsState : public State
    {
    public:
        ProfileExistsState(::GameSession&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
