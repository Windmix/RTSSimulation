#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"
#include "Clock.h"
#include <iostream>


// Remove the processed message from the priority queue
void MessageDispatcher::discharge(std::shared_ptr<BaseGameEntity> spReceiver, Telegram& msg)
{
    if (!spReceiver)
    {
        std::cerr << "Error: Null receiver in MessageDispatcher::discharge" << std::endl;
        return;
    }
    spReceiver->handleMessage(msg);

    // Remove the processed message from the priority queue
    std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> tempQ;
    while (!priorityQ.empty())
    {
        Telegram topMsg = priorityQ.top();
        priorityQ.pop();
        if (topMsg.getIdReceiver() != msg.getIdReceiver())
        {
            tempQ.push(topMsg);
        }
    }
    priorityQ = tempQ;
}

std::shared_ptr<MessageDispatcher> MessageDispatcher::instance()
{
    static std::shared_ptr<MessageDispatcher> messageDispatcher = std::make_shared<MessageDispatcher>();
    return messageDispatcher;
}

void MessageDispatcher::DispatchMsg(int delay, int sender, int receiver, MessageType msg, std::shared_ptr<void> ExtraInfo)
{
    std::shared_ptr<Clock> theClock = Clock::instance();
    std::shared_ptr<BaseGameEntity> SPreceiver = Entity_Manager->getEntityFromID(receiver);
 

    Telegram telegram(delay, sender, receiver, msg, ExtraInfo); // save information

    //TODO ADD TIME AND MAKE IT WORK!! XD

    if (delay <= 0.0f)
    {
        discharge(SPreceiver, telegram);
    }
    else
    {
        telegram.setDispatchTime(theClock->time + delay);

        priorityQ.push(telegram);
    }
}

std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> MessageDispatcher::getPriorityQ()
{
    return this->priorityQ;
}

void MessageDispatcher::setPriorityQ(std::priority_queue<Telegram, std::vector<Telegram>, TelegramComparator> PriorityQ)
{
    this->priorityQ = PriorityQ;
}

void MessageDispatcher::dispatchDelayedMessages()
{
    std::shared_ptr<Clock> theClock = Clock::instance();
    auto localtime = theClock->time;


    while (!priorityQ.empty())
    {
        Telegram telegram = priorityQ.top();  // Get the earliest message
        if (telegram.getDispatchTime() > localtime)  // Not ready to dispatch yet
        {
            break;
        }
        std::shared_ptr<BaseGameEntity> SPreceiver = Entity_Manager->getEntityFromID(telegram.getIdReceiver());
        discharge(SPreceiver, telegram);
        if (!priorityQ.empty())
        {
            priorityQ.pop();  // Remove the processed message
        }
    }
        
}
