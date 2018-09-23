#pragma once


class PlayerSession;

namespace PlayerState
{
    class State
    {
    public:
        State(::PlayerSession&);
    private:
        ::PlayerSession& m_session;
    };
}
