#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <memory>
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
    Account(Account&&);
    const std::string& tagname() const {
        return m_tagname;
    }

	const std::uint8_t* password() const {
		return m_password;
	}

    std::uint8_t* password() {
        return m_password;
    }

    const boost::uuids::uuid& sessionUUID() const {
        return *m_sessionUUID;
    }

    void setPassword(const std::uint8_t*);
    void generateSessionUUID();

private:
    std::string m_tagname;
    std::uint8_t m_password[SHA512_DIGEST_LENGTH];
    std::shared_ptr<boost::uuids::uuid> m_sessionUUID;

    Account(const std::string& tagname, const std::uint8_t*);
};
