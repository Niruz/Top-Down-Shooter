#include "MinerOwnedStates.h"
#include <iostream>

#include "Miner.h"
#include "Vampire.h"
#include "ConsoleUtils.h"
#include "SimpleTimer.h"
#include "MessageTypes.h"
#include "EntityNames.h"
#include "MessageDispatcher.h"
using std::cout;

//------------------------------------------------------------------------methods for EnterMineAndDigForNugget

EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
	static EnterMineAndDigForNugget instance;

	return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
	//if the miner is not already located at the goldmine, he must
	//change location to the gold mine
	if (pMiner->Location() != goldmine)
	{
		cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Walkin' to the goldmine";

		pMiner->ChangeLocation(goldmine);
	}
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{
	//Now the miner is at the goldmine he digs for gold until he
	//is carrying in excess of MaxNuggets. If he gets thirsty during
	//his digging he packs up work for a while and changes state to
	//gp to the saloon for a whiskey.
	pMiner->AddToGoldCarried(1);

	pMiner->IncreaseFatigue();

	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Pickin' up a nugget";

	//if enough gold mined, go and put it in the bank
	if (pMiner->PocketsFull())
	{
		pMiner->GetFSM()->changeState(VisitBankAndDepositGold::Instance());
	}

	if (pMiner->Thirsty())
	{
		pMiner->GetFSM()->changeState(QuenchThirst::Instance());
	}
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": "
		<< "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Message& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;

	return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
	//on entry the miner makes sure he is located at the bank
	if (pMiner->Location() != bank)
	{
		cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Goin' to the bank. Yes siree";

		pMiner->ChangeLocation(bank);
	}
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
	//deposit the gold
	pMiner->AddToWealth(pMiner->GoldCarried());

	pMiner->SetGoldCarried(0);

	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": "
		<< "Depositing gold. Total savings now: " << pMiner->Wealth();

	//wealthy enough to have a well earned rest?
	if (pMiner->Wealth() >= ComfortLevel)
	{
		cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": "
			<< "WooHoo! Rich enough for now. Back home to mah li'lle lady";

		pMiner->GetFSM()->changeState(GoHomeAndSleepTilRested::Instance());
	}

	//otherwise get more gold
	else
	{
		pMiner->GetFSM()->changeState(EnterMineAndDigForNugget::Instance());
	}
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Leavin' the bank";
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Message& msg)
{
	//send msg to global message handler
	return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;

	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
	if (pMiner->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Walkin' home";

		pMiner->ChangeLocation(shack);

		//let the wife know I'm home
		MessageMan->dispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pMiner->GetID(),        //ID of sender
			ent_Elsa,            //ID of recipient
			Msg_HiHoneyImHome,   //the message
			NO_ADDITIONAL_INFO);
	}
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{
	//if miner is not fatigued start to dig for nuggets again.
	if (!pMiner->Fatigued())
	{
		cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": "
			<< "All mah fatigue has drained away. Time to find more gold!";

		pMiner->GetFSM()->changeState(EnterMineAndDigForNugget::Instance());
	}

	else
	{
		//sleep
		pMiner->DecreaseFatigue();

		cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "ZZZZ... ";
	}
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{
}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Message& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.mMsg)
	{
	case Msg_StewReady:

		cout << "\nMessage handled by " << GetNameOfEntity(pMiner->GetID())
			<< " at time: " << Clock->GetCurrentTimeInSeconds();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pMiner->GetID())
			<< ": Okay Hun, ahm a comin'!";

		pMiner->GetFSM()->changeState(EatStew::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;

	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
	if (pMiner->Location() != saloon)
	{
		pMiner->ChangeLocation(saloon);

		cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
	}
}

void QuenchThirst::Execute(Miner* pMiner)
{
	pMiner->BuyAndDrinkAWhiskey();

	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "That's mighty fine sippin' liquer";

	pMiner->GetFSM()->changeState(EnterMineAndDigForNugget::Instance());
}


void QuenchThirst::Exit(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Leaving the saloon, feelin' good";
}


bool QuenchThirst::OnMessage(Miner* pMiner, const Message& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
	static EatStew instance;

	return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStew::Execute(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Tastes real good too!";

	pMiner->GetFSM()->revertToPreviousState();
}

void EatStew::Exit(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool EatStew::OnMessage(Miner* pMiner, const Message& msg)
{
	//send msg to global message handler
	return false;
}





EnterMineAndDigForVampire* EnterMineAndDigForVampire::Instance()
{
	static EnterMineAndDigForVampire instance;

	return &instance;
}


void EnterMineAndDigForVampire::Enter(Vampire* pMiner)
{
	//if the miner is not already located at the goldmine, he must
	//change location to the gold mine
	/*	if (pMiner->Location() != goldmine)
	{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' to the goldmine";

	pMiner->ChangeLocation(goldmine);
	}*/
}


void EnterMineAndDigForVampire::Execute(Vampire* pMiner)
{
	//Now the miner is at the goldmine he digs for gold until he
	//is carrying in excess of MaxNuggets. If he gets thirsty during
	//his digging he packs up work for a while and changes state to
	//gp to the saloon for a whiskey.
	/*pMiner->AddToGoldCarried(1);

	pMiner->IncreaseFatigue();

	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Pickin' up a nugget";

	//if enough gold mined, go and put it in the bank
	if (pMiner->PocketsFull())
	{
	pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}

	if (pMiner->Thirsty())
	{
	pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
	}*/
}


void EnterMineAndDigForVampire::Exit(Vampire* pMiner)
{
	//cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
	//	<< "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool EnterMineAndDigForVampire::OnMessage(Vampire* pMiner, const Message& msg)
{
	//send msg to global message handler
	return false;
}