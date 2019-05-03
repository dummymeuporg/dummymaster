#include "account.hpp"

#include <cstring>
#include <string>

Account::Account(const std::string& tagname) : m_tagname(tagname) {}

Account::Account(const std::string& tagname, const std::uint8_t* password)
    : m_tagname(tagname), m_sessionUUID(nullptr)
{
    setPassword(password);
}

Account::Account(Account&& acc) {
    m_tagname = std::move(acc.m_tagname);
    ::memcpy(m_password, acc.m_password, SHA512_DIGEST_LENGTH);
    m_sessionUUID = std::move(acc.m_sessionUUID);
}

void Account::setPassword(const std::uint8_t* password) {
    ::memcpy(m_password, password, SHA512_DIGEST_LENGTH);
}

void Account::generateSessionUUID() {
    boost::uuids::random_generator gen;
    m_sessionUUID = std::make_shared<boost::uuids::uuid>(gen());
}

