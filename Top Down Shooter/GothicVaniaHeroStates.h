#pragma once
#include "State.h"

class HeroEntity;
//------------------------------------------------------------------------
//
//  Idle state for the hero
//  
//------------------------------------------------------------------------
class HeroIdle : public State<HeroEntity>
{
private:

	HeroIdle() {}

	//copy ctor and assignment should be private
	HeroIdle(const HeroIdle&);
	HeroIdle& operator=(const HeroIdle&);

public:

	//this is a singleton
	static HeroIdle* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir1 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir1() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir1(const HeroAttackSwordAir1&);
	HeroAttackSwordAir1& operator=(const HeroAttackSwordAir1&);

public:

	//this is a singleton
	static HeroAttackSwordAir1* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir2 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir2() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir2(const HeroAttackSwordAir2&);
	HeroAttackSwordAir2& operator=(const HeroAttackSwordAir2&);

public:

	//this is a singleton
	static HeroAttackSwordAir2* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir3 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir3() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir3(const HeroAttackSwordAir3&);
	HeroAttackSwordAir3& operator=(const HeroAttackSwordAir3&);

public:

	//this is a singleton
	static HeroAttackSwordAir3* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir4 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir4() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir4(const HeroAttackSwordAir4&);
	HeroAttackSwordAir4& operator=(const HeroAttackSwordAir4&);

public:

	//this is a singleton
	static HeroAttackSwordAir4* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir5 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir5() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir5(const HeroAttackSwordAir5&);
	HeroAttackSwordAir5& operator=(const HeroAttackSwordAir5&);

public:

	//this is a singleton
	static HeroAttackSwordAir5* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSword1 : public State<HeroEntity>
{
private:

	HeroAttackSword1() {}

	//copy ctor and assignment should be private
	HeroAttackSword1(const HeroAttackSword1&);
	HeroAttackSword1& operator=(const HeroAttackSword1&);

public:

	//this is a singleton
	static HeroAttackSword1* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);
	
	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSword2 : public State<HeroEntity>
{
private:

	HeroAttackSword2() {}

	//copy ctor and assignment should be private
	HeroAttackSword2(const HeroAttackSword2&);
	HeroAttackSword2& operator=(const HeroAttackSword2&);

public:

	//this is a singleton
	static HeroAttackSword2* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSword3 : public State<HeroEntity>
{
private:

	HeroAttackSword3() {}

	//copy ctor and assignment should be private
	HeroAttackSword3(const HeroAttackSword3&);
	HeroAttackSword3& operator=(const HeroAttackSword3&);

public:

	//this is a singleton
	static HeroAttackSword3* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Crouch state for the hero
//  
//------------------------------------------------------------------------
class HeroCrouch : public State<HeroEntity>
{
private:

	HeroCrouch() {}

	//copy ctor and assignment should be private
	HeroCrouch(const HeroCrouch&);
	HeroCrouch& operator=(const HeroCrouch&);

public:

	//this is a singleton
	static HeroCrouch* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Running state for the hero
//  
//------------------------------------------------------------------------
class HeroRunning : public State<HeroEntity>
{
private:

	HeroRunning() {}

	//copy ctor and assignment should be private
	HeroRunning(const HeroRunning&);
	HeroRunning& operator=(const HeroRunning&);

public:

	//this is a singleton
	static HeroRunning* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Running state for the hero
//  
//------------------------------------------------------------------------
class HeroSliding : public State<HeroEntity>
{
private:

	HeroSliding() {}

	//copy ctor and assignment should be private
	HeroSliding(const HeroSliding&);
	HeroSliding& operator=(const HeroSliding&);

public:

	//this is a singleton
	static HeroSliding* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Falling state for the hero
//  
//------------------------------------------------------------------------
class HeroFalling : public State<HeroEntity>
{
private:

	HeroFalling() {}

	//copy ctor and assignment should be private
	HeroFalling(const HeroFalling&);
	HeroFalling& operator=(const HeroFalling&);

public:

	//this is a singleton
	static HeroFalling* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//
//  Jumping state for the hero
//  
//------------------------------------------------------------------------
class HeroJumping : public State<HeroEntity>
{
private:

	HeroJumping() {}

	//copy ctor and assignment should be private
	HeroJumping(const HeroJumping&);
	HeroJumping& operator=(const HeroJumping&);

public:

	//this is a singleton
	static HeroJumping* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroDamaged : public State<HeroEntity>
{
private:

	HeroDamaged() {}

	//copy ctor and assignment should be private
	HeroDamaged(const HeroJumping&);
	HeroDamaged& operator=(const HeroJumping&);

public:

	//this is a singleton
	static HeroDamaged* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroFireBowGround : public State<HeroEntity>
{
private:

	HeroFireBowGround() {}

	//copy ctor and assignment should be private
	HeroFireBowGround(const HeroFireBowGround&);
	HeroFireBowGround& operator=(const HeroFireBowGround&);

public:

	//this is a singleton
	static HeroFireBowGround* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroFireBowAir : public State<HeroEntity>
{
private:

	HeroFireBowAir() {}

	//copy ctor and assignment should be private
	HeroFireBowAir(const HeroFireBowAir&);
	HeroFireBowAir& operator=(const HeroFireBowAir&);

public:

	//this is a singleton
	static HeroFireBowAir* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroDie : public State<HeroEntity>
{
private:

	HeroDie() {}

	//copy ctor and assignment should be private
	HeroDie(const HeroDie&);
	HeroDie& operator=(const HeroDie&);

public:

	//this is a singleton
	static HeroDie* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroDropKick : public State<HeroEntity>
{
private:

	HeroDropKick() {}

	//copy ctor and assignment should be private
	HeroDropKick(const HeroDropKick&);
	HeroDropKick& operator=(const HeroDropKick&);

public:

	//this is a singleton
	static HeroDropKick* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroCastSpell : public State<HeroEntity>
{
private:

	HeroCastSpell() {}

	//copy ctor and assignment should be private
	HeroCastSpell(const HeroCastSpell&);
	HeroCastSpell& operator=(const HeroCastSpell&);

public:

	//this is a singleton
	static HeroCastSpell* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroSheatheSword : public State<HeroEntity>
{
private:

	HeroSheatheSword() {}

	//copy ctor and assignment should be private
	HeroSheatheSword(const HeroSheatheSword&);
	HeroSheatheSword& operator=(const HeroSheatheSword&);

public:

	//this is a singleton
	static HeroSheatheSword* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};



/*********************************************
************************************************
*************************************************
**************************************************
BEGINNNING OF THE MELEE STATES*/
/*********************************************
************************************************
*************************************************
**************************************************
BEGINNNING OF THE MELEE STATES*/
/*********************************************
************************************************
*************************************************
**************************************************
BEGINNNING OF THE MELEE STATES*/
/*********************************************
************************************************
*************************************************
**************************************************
BEGINNNING OF THE MELEE STATES*/
/*********************************************
************************************************
*************************************************
**************************************************
BEGINNNING OF THE MELEE STATES*/

//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeIdle : public State<HeroEntity>
{
private:

	HeroMeleeIdle() {}

	//copy ctor and assignment should be private
	HeroMeleeIdle(const HeroMeleeIdle&);
	HeroMeleeIdle& operator=(const HeroMeleeIdle&);

public:

	//this is a singleton
	static HeroMeleeIdle* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeRun : public State<HeroEntity>
{
private:

	HeroMeleeRun() {}

	//copy ctor and assignment should be private
	HeroMeleeRun(const HeroMeleeRun&);
	HeroMeleeRun& operator=(const HeroMeleeRun&);

public:

	//this is a singleton
	static HeroMeleeRun* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeDrawSword : public State<HeroEntity>
{
private:

	HeroMeleeDrawSword() {}

	//copy ctor and assignment should be private
	HeroMeleeDrawSword(const HeroMeleeDrawSword&);
	HeroMeleeDrawSword& operator=(const HeroMeleeDrawSword&);

public:

	//this is a singleton
	static HeroMeleeDrawSword* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeSliding : public State<HeroEntity>
{
private:

	HeroMeleeSliding() {}

	//copy ctor and assignment should be private
	HeroMeleeSliding(const HeroMeleeSliding&);
	HeroMeleeSliding& operator=(const HeroMeleeSliding&);

public:

	//this is a singleton
	static HeroMeleeSliding* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//------------------------------------------------------------------------
//
//  Falling state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeFalling : public State<HeroEntity>
{
private:

	HeroMeleeFalling() {}

	//copy ctor and assignment should be private
	HeroMeleeFalling(const HeroMeleeFalling&);
	HeroMeleeFalling& operator=(const HeroMeleeFalling&);

public:

	//this is a singleton
	static HeroMeleeFalling* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeDamaged : public State<HeroEntity>
{
private:

	HeroMeleeDamaged() {}

	//copy ctor and assignment should be private
	HeroMeleeDamaged(const HeroMeleeDamaged&);
	HeroMeleeDamaged& operator=(const HeroMeleeDamaged&);

public:

	//this is a singleton
	static HeroMeleeDamaged* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeJump : public State<HeroEntity>
{
private:

	HeroMeleeJump() {}

	//copy ctor and assignment should be private
	HeroMeleeJump(const HeroMeleeJump&);
	HeroMeleeJump& operator=(const HeroMeleeJump&);

public:

	//this is a singleton
	static HeroMeleeJump* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeKick1 : public State<HeroEntity>
{
private:

	HeroMeleeKick1() {}

	//copy ctor and assignment should be private
	HeroMeleeKick1(const HeroMeleeKick1&);
	HeroMeleeKick1& operator=(const HeroMeleeKick1&);

public:

	//this is a singleton
	static HeroMeleeKick1* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeKick2 : public State<HeroEntity>
{
private:

	HeroMeleeKick2() {}

	//copy ctor and assignment should be private
	HeroMeleeKick2(const HeroMeleeKick2&);
	HeroMeleeKick2& operator=(const HeroMeleeKick2&);

public:

	//this is a singleton
	static HeroMeleeKick2* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeDropKick : public State<HeroEntity>
{
private:

	HeroMeleeDropKick() {}

	//copy ctor and assignment should be private
	HeroMeleeDropKick(const HeroMeleeDropKick&);
	HeroMeleeDropKick& operator=(const HeroMeleeDropKick&);

public:

	//this is a singleton
	static HeroMeleeDropKick* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleePunch1 : public State<HeroEntity>
{
private:

	HeroMeleePunch1() {}

	//copy ctor and assignment should be private
	HeroMeleePunch1(const HeroMeleePunch1&);
	HeroMeleePunch1& operator=(const HeroMeleePunch1&);

public:

	//this is a singleton
	static HeroMeleePunch1* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleePunch2 : public State<HeroEntity>
{
private:

	HeroMeleePunch2() {}

	//copy ctor and assignment should be private
	HeroMeleePunch2(const HeroMeleePunch2&);
	HeroMeleePunch2& operator=(const HeroMeleePunch2&);

public:

	//this is a singleton
	static HeroMeleePunch2* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleePunch3 : public State<HeroEntity>
{
private:

	HeroMeleePunch3() {}

	//copy ctor and assignment should be private
	HeroMeleePunch3(const HeroMeleePunch3&);
	HeroMeleePunch3& operator=(const HeroMeleePunch3&);

public:

	//this is a singleton
	static HeroMeleePunch3* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};

//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroKnockedDownMelee : public State<HeroEntity>
{
private:

	HeroKnockedDownMelee() {}

	//copy ctor and assignment should be private
	HeroKnockedDownMelee(const HeroKnockedDownMelee&);
	HeroKnockedDownMelee& operator=(const HeroKnockedDownMelee&);

public:

	//this is a singleton
	static HeroKnockedDownMelee* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroMeleeGetUp : public State<HeroEntity>
{
private:

	HeroMeleeGetUp() {}

	//copy ctor and assignment should be private
	HeroMeleeGetUp(const HeroMeleeGetUp&);
	HeroMeleeGetUp& operator=(const HeroMeleeGetUp&);

public:

	//this is a singleton
	static HeroMeleeGetUp* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};

//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroKnockedDownSword : public State<HeroEntity>
{
private:

	HeroKnockedDownSword() {}

	//copy ctor and assignment should be private
	HeroKnockedDownSword(const HeroKnockedDownSword&);
	HeroKnockedDownSword& operator=(const HeroKnockedDownSword&);

public:

	//this is a singleton
	static HeroKnockedDownSword* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroSwordGetUp : public State<HeroEntity>
{
private:

	HeroSwordGetUp() {}

	//copy ctor and assignment should be private
	HeroSwordGetUp(const HeroSwordGetUp&);
	HeroSwordGetUp& operator=(const HeroSwordGetUp&);

public:

	//this is a singleton
	static HeroSwordGetUp* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroDamagedAir : public State<HeroEntity>
{
private:

	HeroDamagedAir() {}

	//copy ctor and assignment should be private
	HeroDamagedAir(const HeroDamagedAir&);
	HeroDamagedAir& operator=(const HeroDamagedAir&);

public:

	//this is a singleton
	static HeroDamagedAir* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};