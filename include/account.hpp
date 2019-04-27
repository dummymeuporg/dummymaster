#pragma once

#include <string>
#include "crypto/sha512.hpp"


class AccountError : public virtual std::exception {

};

class AccountNotFound : public AccountError {
    virtual const char* what() const throw() {
        return "the account does not exist.";
    }
};

class WrongCredentials : public AccountError {
    virtual const char* what() const throw() {
        return "The username and password do not match.";
    }
};


class Account {
public:
    Account(const std::string& tagname);
    const std::string& tagname() const {
        return m_tagname;
    }

	const std::uint8_t* password() const {
		return m_password;
	}

    std::uint8_t* password() {
        return m_password;
    }

    void setPassword(const std::uint8_t*);

private:
    std::string m_tagname;
    std::uint8_t m_password[SHA512_DIGEST_LENGTH];

    Account(const std::string& tagname, const std::uint8_t*);
};
