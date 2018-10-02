#include "MessageDispatcher.h"
#include "Message.h"
#include "EntityManager.h"
#include "SimpleTimer.h"
#include "Entity.h"


MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;

	return &instance;
}

void MessageDispatcher::Discharge(Entity* receiver, const Message& msg)
{
	if(! receiver->handleMessage(msg) )
	{
		std::cout << "Message not handled";
	}
}

void MessageDispatcher::dispatchMessage(double delay, int sender, int receiver, int msg, void* extraInfo)
{
	Entity* pSender   = EntityMan->getEntityFromID(sender);
	Entity* pReceiver = EntityMan->getEntityFromID(receiver);

	if (pReceiver == nullptr)
	{
		std::cout << "\nWarning! No Receiver with ID of " << receiver << " found";
	}

	Message message(0, sender, receiver, msg, extraInfo);

	if(delay <= 0.0f)
	{
		std::cout << "\nInstant telegram dispatched at time: " << Clock->GetCurrentTime()
			<< " by " << pSender->getName() << " for " << pReceiver->getName();
//			<< ". Msg is " << MsgToStr(msg);

		Discharge(pReceiver, message);
	}

	else
	{
		double CurrentTime = Clock->GetCurrentTime();

		message.dispatchTime = CurrentTime + delay;

		PriorityQ.insert(message);

		std::cout << "\nDelayed telegram from " << pSender->getName()<< " recorded at time "
			<< Clock->GetCurrentTime() << " for " << pReceiver->getName();
			//<< ". Msg is " << MsgToStr(msg);
	}
}

void MessageDispatcher::dispatchDelayedMessages()
{
	double CurrentTime = Clock->GetCurrentTime();

	while (!PriorityQ.empty() &&
		(PriorityQ.begin()->dispatchTime < CurrentTime) &&
		(PriorityQ.begin()->dispatchTime > 0))
	{
		//read the telegram from the front of the queue
		const Message& message = *PriorityQ.begin();

		//find the recipient
		Entity* pReceiver = EntityMan->getEntityFromID(message.mReceiver);

		std::cout << "\nQueued telegram ready for dispatch: Sent to "
			<< pReceiver->getName() << ". Msg is " << message.mMsg;

		//send the telegram to the recipient
		Discharge(pReceiver, message);

		//remove it from the queue
		PriorityQ.erase(PriorityQ.begin());
	}

}