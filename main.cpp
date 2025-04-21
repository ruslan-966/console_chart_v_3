#include <iostream>
#include <Windows.h>
#include <memory>
#include "Message.h"
#include "Array.h"
#include "User.h"
#include "ConversationManager.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Array <Message> privateMessagePool;
	Array <Message> commonMessagePool;

	//собственно текст программы:
	std::unique_ptr<ConversationManager> cm(new ConversationManager(privateMessagePool, commonMessagePool));		//создаем экземпляр менеджера обмена данных с пользователем 
	cm->start();
	return 0;
}