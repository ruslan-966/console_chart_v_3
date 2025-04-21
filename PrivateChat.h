#pragma once
#include "Array.h"

class PrivateChat
{
private:
	int _firstPartNumber{ 0 };			//Номер  первого участника в DataManager
	int _secondPartNumber{ 0 };			//Номер второго участника в DataManager
	int _lstMesOneNum{ 0 };				//Номер последнего выведенного сообдения в чате для первого пользователя
	int _lstMesSecondNum{ 0 };			//Номер последнего выведенного сообдения в чате для второго пользователя
	Array<int> _massive;

public:
	PrivateChat() = default;
	PrivateChat(int, int);
	void setMesNumber(int);
	bool isItRightChat(int);			//возвращает информацию, есть ли пользователь в этом чате 
	int getAnotherUser(int);			//возвращает номер второго пользователя
	int getFrstUser();				//возвращает номер первого пользователя
	void printAllPartners();		//Выводит номера двух пользователей на консоль
	bool isTwoUsersOk(int, int);		//сравнивает номера юзеров, при полном совпадении, возвращает true
	Array<int> getArr();				//возвращает контейнер с массивами
	void printArr();					// Выводит содержимое массива в консоль
};
