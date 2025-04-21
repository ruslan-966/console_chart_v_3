#pragma once
#include <string>

class Message
{
private:
	int _numMessage{ 0 };
	std::string _message{ "" };
	std::string _sendFrom{ "" };
	std::string _sendTo{ "" };
	bool _wasItPrinted{ false };
public:
	// Конструкторы:
	Message();
	Message(int, std::string, std::string, std::string);
	Message(int, std::string&, std::string&);
	Message(int, std::string&);


	// Деструктор
	~Message() = default;

	// Сеттеры:
	void setNumMessage(int);
	void setMessage(std::string&);
	void setSendFrom(std::string&);
	void setSendTo(std::string&);

	//Геттеры:
	int getNumMessage() const;
	std::string* getMessage();
	std::string* getSendFrom();
	std::string* getSendTo();
	bool wasItPrinted() const;

	//Операторы
	bool operator==(const Message& other);
};

