#include "MinersWife.h"

bool MinersWife::HandleMessage(const Message& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void MinersWife::Update()
{
	//set text color to green
//	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->update();
}