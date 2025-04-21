#include "UserManager.h"
#include <iostream>

bool UserManager::addUser(User&& user)
{
	if (!exists(move(user.getNickname()), move(user.getLogin())))
	{
		_users->add(std::move(user));
		std::cout << "Пользователь " << user.getNickname() << " успешно зарегистрирован!" << std::endl;
		return true;
	}
	std::cout << "Пользователь с таким ником или логином уже зарегистрирован!" << std::endl;
	return false;
}

User UserManager::getUser(int id) const
{
	return _users->get(id);
}

User UserManager::getCurrentUser() const
{
	return *currentUser;
}

bool UserManager::findUser(User&& user, int& index)
{
	return (_users->find(std::move(user), index)) ? true : false;
}

bool UserManager::exists(std::string&& nickname, std::string&& login)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getNickname() == nickname || _users->get(i).getLogin() == login)
		{
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByNickname(std::string&& nickname, int& index)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getNickname() == nickname)
		{
			index = i;
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByNickname(std::string&& nickname)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getNickname() == nickname)
		{
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByLogin(std::string&& login, int& index)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getLogin() == login)
		{
			index = i;
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByLogin(std::string&& login)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getLogin() == login)
		{
			return true;
		}
	}
	return false;
}

bool UserManager::loginUser(std::string&& login, std::string&& password)
{
	int index = -1;

	if (findUserByLogin(move(login), index) && _users->get(index).checkPassword(std::move(password)))
	{
		std::cout << "Успешный вход в чат!" << std::endl;
		currentUser = std::make_unique<User>(_users->get(index));
		return true;
	}

	std::cout << "Неверный логин или пароль!" << std::endl;
	return false;

}

void UserManager::showUsers()
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		std::cout << "ID: " << i << " " << " Никнейм: " << _users->get(i).getLogin() << std::endl;
	}
}

int UserManager::getCount() const
{
	return _users->getCount();
}

int UserManager::getPosNumber(std::string& name)
{
	for (int i = 0; i < _users->getCount(); ++i)
	{
		if (_users->get(i).getNickname() == name)
			return i;
	}
	return -1;
}
