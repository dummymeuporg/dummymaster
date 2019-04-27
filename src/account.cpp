#include "account.hpp"

#include <cstring>
#include <string>

Account::Account(const std::string& tagname) : m_tagname(tagname) {}

Account::Account(const std::string& tagname, const std::uint8_t* password)
    : m_tagname(tagname)
{
    setPassword(password);
}

void Account::setPassword(const std::uint8_t* password) {
    ::memcpy(m_password, password, SHA512_DIGEST_LENGTH);
}
