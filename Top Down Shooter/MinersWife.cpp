#include "MinersWife.h"

bool MinersWife::handleMessage(const Message& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void MinersWife::update()
{
	//set text color to green
//	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->update();
}