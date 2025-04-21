#pragma once
#include "User.h"
#include "DataManager.h"
#include "Array.h"
#include <memory>
#include <string>


class UserManager //класс для управления пользователями
{
public:
	UserManager(std::unique_ptr<DataManager<User>>&& manager) : _users(std::move(manager)) {};
	UserManager() = default;
	bool addUser(User&& user);
	User getUser(int id) const;
	User getCurrentUser() const;
	bool findUser(User&& user, int& index);
	bool exists(std::string&&, std::string&&);
	bool findUserByNickname(std::string&& nickname, int& index);
	bool findUserByNickname(std::string&& nickname);
	bool findUserByLogin(std::string&& login, int& index);
	bool findUserByLogin(std::string&& login);
	bool loginUser(std::string&& login, std::string&& password);
	void showUsers();
	int getCount() const;
	int getPosNumber(std::string&);
private:
	std::unique_ptr<DataManager<User>> _users;
	std::unique_ptr<User> currentUser;
};