#define BOOST_LOG_DYN_LINK 1

#include <iostream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "player_session.hpp"
#include "players_server.hpp"

#include "player_state/right_credentials_state.hpp"


PlayerState::RightCredentialsState::RightCredentialsState(
    ::PlayerSession& session,
    std::shared_ptr<::Account> account
) : PlayerState::State(session)
{
    PlayersServer& server(m_session.playersServer());
    // Check if the account is connected. Refuse the connection if
    // that is the case.
    if (server.isAccountConnected(account->tagname())) {
        // return some error.
        std::cerr << "Account " << account->tagname() << " already connected.";
    }

    // Otherwise, connect the account.
    std::cerr << "Connect account " << account->tagname() << std::endl;
    server.connectAccount(std::move(*account));
    // Send list of connected game servers?
}

void PlayerState::RightCredentialsState::onRead(
        const std::vector<std::uint8_t>&buffer)
{

}
