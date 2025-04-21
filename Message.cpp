#include "Message.h"

Message::Message()
{
}

Message::Message(int numMessage, std::string message, std::string sendFrom, std::string sendTo)
{
	_numMessage = numMessage;
	_message = message;
	_sendFrom = sendFrom;
	_sendTo = sendTo;
}

Message::Message(int numMessage, std::string& message, std::string& sendFrom)
{
	_numMessage = numMessage;
	_message = message;
	_sendFrom = sendFrom;
	_sendTo = std::string{ "All" };
}

Message::Message(int numMessage, std::string& message)
{
	_numMessage = numMessage;
	_message = message;
}

void Message::setNumMessage(int numMessage)
{
	_numMessage = numMessage;
}

void Message::setMessage(std::string& message)
{
	_message = message;
}

void Message::setSendFrom(std::string& sendFrom)
{
	_sendFrom = sendFrom;
}

void Message::setSendTo(std::string& sendTo)
{
	_sendTo = sendTo;
}

int Message::getNumMessage() const
{
	return _numMessage;
}

std::string* Message::getMessage()
{
	return &_message;
}

std::string* Message::getSendFrom()
{
	return &_sendFrom;
}

std::string* Message::getSendTo()
{
	return &_sendTo;
}

bool Message::wasItPrinted() const
{
	return _wasItPrinted;
}

bool Message::operator==(const Message& other)
{
	return (_message == other._message) ? true : false;
}
