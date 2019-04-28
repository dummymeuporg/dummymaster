#pragma once

#include "player_state/state.hpp"

namespace PlayerState
{
    class WrongCredentialsState : public State
    {
    public:
        WrongCredentialsState(::PlayerSession&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
