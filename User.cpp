#include "User.h"

std::string User::getNickname()	const
{
	return _nickname;
}

std::string User::getLogin() const
{
	return _login;
}

std::string User::getPassword() const
{
	return _password;
}

void User::setNickname(std::string&& nickname)
{
	_nickname = nickname;
}

void User::setLogin(std::string&& login)
{
	_login = login;
}

void User::setPassword(std::string&& password)
{
	_password = password;
}

bool User::checkPassword(std::string&& password) const
{
	return (_password == password) ? true : false;
}

bool User::operator==(const User& b)
{
	if (_login == b._login && _nickname == b._nickname && _password == b._password) return true;
	return false;
}