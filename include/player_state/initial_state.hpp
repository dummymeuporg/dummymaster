#pragma once

#include "player_state/state.hpp"

namespace PlayerState
{
    class InitialState : public State
    {
    public:
        InitialState(::PlayerSession&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
