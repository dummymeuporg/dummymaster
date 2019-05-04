#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class PlayerSession;

namespace PlayerState
{
    class State : public std::enable_shared_from_this<State>
    {
    public:
        State(::PlayerSession&);
        virtual void onRead(const std::vector<std::uint8_t>&) = 0;
    protected:
        ::PlayerSession& m_session;
    };
}
