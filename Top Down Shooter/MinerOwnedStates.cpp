#include "MinerOwnedStates.h"
#include <iostream>
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
/*	if (pMiner->Location() != goldmine)
	{
		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' to the goldmine";

		pMiner->ChangeLocation(goldmine);
	}*/
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
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


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
	//cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
	//	<< "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Message& msg)
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