#include "Telegram.h"


Telegram::Telegram() // know who is calling and who is being called
{
	this->dispatchTime = 0;
	this->idSender = 0;
	this->idReceiver = 0;
	this->extraInfo = nullptr;
}

Telegram::Telegram(int delay, int sender, int receiver, MessageType msg, std::shared_ptr<void> ExtraInfo)
{
	this->dispatchTime = delay;
	this->idSender = sender;
	this->idReceiver = receiver;
	this->message = msg;
	this->extraInfo = extraInfo;
}

int Telegram::getIdSender()
{
	return this->idSender;
}

void Telegram::setIdSender(int id)
{
	this->idSender = id;
}

int Telegram::getIdReceiver()
{
	return this->idReceiver;
}

void Telegram::setIdReceiver(int id)
{
	this->idReceiver = id;
}

MessageType Telegram::getMessage()
{
	return this->message;
}

void Telegram::setMessage(MessageType mesasge)
{
	this->message = message;
}

int Telegram::getDispatchTime()
{
	return this->dispatchTime;
}

void Telegram::setDispatchTime(int disTime)
{
	this->dispatchTime = disTime;
}


