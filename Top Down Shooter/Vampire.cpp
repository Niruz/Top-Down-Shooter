#include "Vampire.h"

void Vampire::update()
{

}
bool Vampire::handleMessage(const Message& msg)
{
	return mStateMachine->HandleMessage(msg);
}