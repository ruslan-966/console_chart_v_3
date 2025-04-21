#pragma once
#include <iostream>
#include <conio.h> // подключаем getch
#include <ios>		// for <streamsize>
#include <limits>	// for numeric_limits
#include <memory>	// для умных указателей

#include "User.h"
#include "Array.h"
#include "Message.h"
#include "getRightInt.cpp"
#include "UserManager.h"
#include "PrivateChat.h"

class ConversationManager
{
public:
	//Конструкторы
	ConversationManager();
	ConversationManager(Array <Message>&, Array <Message>&);

	void cleanConsole();
	void start();
	void greeting();								//Начальное приветствие пользователя 
	char regOrComm();								//Меню выбора регистрации нового участника или общения
	bool userRegistration();						//Диалог регистрации нового пользователя
	int usersInput();								//Вход зарегистрированного пользователя
	void userMessChoise(User&);						//Меню общего и личного чатов
	
	void outputPrivateMesage(User&);				//Вывод на консоль сообщений из личного чата
	void outputCommonMessage();						//Вывод на консоль сообщений из общего чата
	void inputPrivateMessage(User&);				//Запись сообщения в личтный чат
	void inputCommonMessage(std::string&);			//Запись сообщения в общий чат
	int amountPrivateMessage(std::string&);			//Количество личных сообщений для одного пользователя
	void privateMesMenu(std::string&);				//Меню работы с личными сообщениями
	void readWritePrivateChat(int, int);			//Работа с конкретным чатом
	void createNewChart(int, Array<int>&);			//Создание нового чата
	void writeNewChart(int, int);					//Запись данных нового чата
	void printPrivateMessagePool();					//Выводит на консоль содержимое массива

	Array <Message> privateMessagePool;
	Array <Message> commonMessagePool;
	UserManager allUsers;
	Array <PrivateChat*> ptrPrivCharts;
};

