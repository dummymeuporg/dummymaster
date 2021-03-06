#pragma once

#include <memory>

#include "account.hpp"

#include "player_state/state.hpp"

namespace PlayerState
{
    class RightCredentialsState : public State
    {
    public:
        RightCredentialsState(::PlayerSession&, std::shared_ptr<::Account>);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
