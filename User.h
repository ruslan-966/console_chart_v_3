#pragma once
#include <string>

class User
{
public:

	User(std::string login, std::string nickname, std::string password) :
		_login(login), _nickname(nickname), _password(password) {
	}
	User() = default;
	std::string getNickname() const;
	std::string getLogin() const;
	std::string getPassword() const;
	void setNickname(std::string&& _nickname);
	void setLogin(std::string&& _login);
	void setPassword(std::string&& _password);
	bool checkPassword(std::string&& _password) const;
	bool operator==(const User& b);

private:

	std::string _login;
	std::string _nickname;
	std::string _password;

};