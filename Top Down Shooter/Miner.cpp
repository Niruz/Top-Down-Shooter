#include "Miner.h"

void Miner::update()
{

}
bool Miner::handleMessage(const Message& msg)
{
	return mStateMachine->HandleMessage(msg);
}