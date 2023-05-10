#pragma once
#include <string>
#include <exception>
#include "Sha1.h"

struct UserLoginException : public std::exception  
{
	const char* what() const noexcept override { return "\n Login is already taken, please enter another one! \n"; }
};

struct UserPasswordException : public std::exception
{
	const char* what() const noexcept override { return "\n Password length must be between 4 and 8 numbers or letters \n"; }
};

class User
{
public:

	enum EnStatus {free, engaged, deleted };

	User() :
		_login(),
		_pass_sha1_hash(0),
		_status(EnStatus::free) {}
	
	 User(std::string& login, uint* sh1) {_login = login; _pass_sha1_hash = sh1; _status = EnStatus::engaged;}
	
	 User& operator = (const User& other) {
		_login = other._login;

		if (_pass_sha1_hash != 0)
			delete[] _pass_sha1_hash;
		_pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

		memcpy(_pass_sha1_hash, other._pass_sha1_hash, SHA1HASHLENGTHBYTES);
		_status = other._status;

		return *this;
	 }

	 const std::string& GetLogin() const { return _login; }
	 int GetStatus() { return _status; }
	 uint* GetPassword() const { return _pass_sha1_hash; }
	 void SetPassword(uint* password) { memcpy(_pass_sha1_hash, password, SHA1HASHLENGTHBYTES); }

private:
	EnStatus _status;
	std::string _login;
	uint* _pass_sha1_hash;

};