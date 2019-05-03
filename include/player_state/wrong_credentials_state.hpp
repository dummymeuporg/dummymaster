#pragma once

#include "player_state/state.hpp"

namespace PlayerState
{
    class WrongCredentialsState : public State
    {
    public:
        WrongCredentialsState(::PlayerSession&, unsigned int attempts);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    private:
        unsigned int m_attempts;
    };
}
