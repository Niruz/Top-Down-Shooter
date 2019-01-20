#pragma once
#include "BaseEnemy.h"
#include "TileMap.h"
class ShakeInfo;
//Simple enemy that prols back and forth, might try and go for the player later
struct BigSkeletonEntity : public BaseEnemy
{
	StateMachine<BigSkeletonEntity>*  myStateMachine;
	StateMachine<BigSkeletonEntity>*  GetFSM()const { return myStateMachine; }
	BigSkeletonEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~BigSkeletonEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();
	void SetAnimation(const std::string& name);

	void ResetAttackTimer();
	void SetFacing();

	bool IsPlayerWithinPatrolRange();
	bool IsPlayerWithinAttackDistance();
	bool AmIWithinMyPatrolDistance();
	bool IsPlayerToTheRight();
	bool IsAttackCoolDownReady();
	void HandleDamaged(int damageRecieved);
public:

	//Bad design...
	TileMap * myTileMap;
	ShakeInfo* myShakeInfoSlamAttack;
	float myAttackCooldown;
	bool myAlreadyAttacked;
};