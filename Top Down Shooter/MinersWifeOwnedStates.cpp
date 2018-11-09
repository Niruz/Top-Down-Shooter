#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWife.h"
#include "Locations.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "SimpleTimer.h"
#include <iostream>
#include "EntityNames.h"
#include "ConsoleUtils.h"
#include "Utils.h"
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

WifesGlobalState* WifesGlobalState::Instance()
{
	static WifesGlobalState instance;

	return &instance;
}


void WifesGlobalState::Execute(MinersWife* wife)
{
	//1 in 10 chance of needing the bathroom (provided she is not already
	//in the bathroom)
	if ((RandFloat() < 0.1) &&
		!wife->GetFSM()->isInState(*VisitBathroom::Instance()))
	{
		wife->GetFSM()->changeState(VisitBathroom::Instance());
	}
}

bool WifesGlobalState::OnMessage(MinersWife* wife, const Message& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.mMsg)
	{
	case Msg_HiHoneyImHome:
	{
		cout << "\nMessage handled by " << "Elsa" << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n" << "Elsa" <<
			": Hi honey. Let me make you some of mah fine country stew";

		wife->GetFSM()->changeState(CookStew::Instance());
	}

	return true;

	}//end switch

	return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork* DoHouseWork::Instance()
{
	static DoHouseWork instance;

	return &instance;
}


void DoHouseWork::Enter(MinersWife* wife)
{
	cout << "\n" << "Elsa" << ": Time to do some more housework!";
}


void DoHouseWork::Execute(MinersWife* wife)
{
	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << "Elsa" << ": Moppin' the floor";

		break;

	case 1:

		cout << "\n" << "Elsa" << ": Washin' the dishes";

		break;

	case 2:

		cout << "\n" << "Elsa" << ": Makin' the bed";

		break;
	}
}

void DoHouseWork::Exit(MinersWife* wife)
{
}

bool DoHouseWork::OnMessage(MinersWife* wife, const Message& msg)
{
	return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom* VisitBathroom::Instance()
{
	static VisitBathroom instance;

	return &instance;
}


void VisitBathroom::Enter(MinersWife* wife)
{
	cout << "\n" << "Elsa" << ": Walkin' to the can. Need to powda mah pretty li'lle nose";
}


void VisitBathroom::Execute(MinersWife* wife)
{
	cout << "\n" << "Elsa" << ": Ahhhhhh! Sweet relief!";

	wife->GetFSM()->revertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife)
{
	cout << "\n" << "Elsa" << ": Leavin' the Jon";
}


bool VisitBathroom::OnMessage(MinersWife* wife, const Message& msg)
{
	return false;
}


//------------------------------------------------------------------------CookStew

CookStew* CookStew::Instance()
{
	static CookStew instance;

	return &instance;
}


void CookStew::Enter(MinersWife* wife)
{
	//if not already cooking put the stew in the oven
	if (!wife->Cooking())
	{
		cout << "\n" << "Elsa" << ": Putting the stew in the oven";

		//send a delayed message myself so that I know when to take the stew
		//out of the oven
		MessageMan->dispatchMessage(1.5,                  //time delay
			wife->GetID(),           //sender ID
			wife->GetID(),           //receiver ID
			Msg_StewReady,        //msg
			NO_ADDITIONAL_INFO);

		wife->SetCooking(true);
	}

}


void CookStew::Execute(MinersWife* wife)
{
	cout << "\n" << "Elsa" << ": Fussin' over food";
}

void CookStew::Exit(MinersWife* wife)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << "Elsa" << ": Puttin' the stew on the table";
}


bool CookStew::OnMessage(MinersWife* wife, const Message& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.mMsg)
	{
	case Msg_StewReady:
	{
		cout << "\nMessage received by " <<"Elsa" <<
			" at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << "Elsa" << ": StewReady! Lets eat";

		//let hubby know the stew is ready
		MessageMan->dispatchMessage(SEND_MSG_IMMEDIATELY,
			wife->GetID(),
			ent_Miner_Bob,
			Msg_StewReady,
			NO_ADDITIONAL_INFO);

		wife->SetCooking(false);

		wife->GetFSM()->changeState(DoHouseWork::Instance());
	}

	return true;

	}//end switch

	return false;
}