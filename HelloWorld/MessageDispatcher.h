#pragma once
#include "BaseGameEntity.h"
#include <memory>
#include "Telegram.h"
#include <queue>
#include <vector>
#include "DataControllerTrees.h"


struct TelegramComparator
{
	bool operator()(Telegram& t1, Telegram& t2)
	{
		return t1.getDispatchTime() > t2.getDispatchTime();  // Min-heap (earlier dispatch time first)
	}
};

class MessageDispatcher
{
private:
	std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> priorityQ;
	void discharge(std::shared_ptr<BaseGameEntity> spReceiver, Telegram& msg);

public:

	MessageDispatcher() {}
	static std::shared_ptr<MessageDispatcher> instance();

	void DispatchMsg(int delay, int sender, int receiver, MessageType msg, std::shared_ptr<void> ExtraInfo);
	std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> getPriorityQ();
	void setPriorityQ(std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> PriorityQ);

	//send out any delayed messages. This method is called each time through
	// the main game loop.
	void dispatchDelayedMessages();
};
//to make life easier...
#define Dispatch MessageDispatcher::Instance()