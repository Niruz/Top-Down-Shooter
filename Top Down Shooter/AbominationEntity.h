#pragma once
#include "BaseEnemy.h"
#include "TileMap.h"
class ShakeInfo;
//Simple enemy that prols back and forth, might try and go for the player later
struct AbominationEntity : public BaseEnemy
{
	StateMachine<AbominationEntity>*  myStateMachine;
	StateMachine<AbominationEntity>*  GetFSM()const { return myStateMachine; }
	AbominationEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~AbominationEntity();

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
	void StartJump();
	void HandleJump();
	void HandleFalling();

	bool IsPlayerWithinAttackDistance2();
public:

	//Bad design...
	TileMap * myTileMap;
	ShakeInfo* myShakeInfoSlamAttack;
	ShakeInfo* myJumpShake;
	float myAttackCooldown;
	bool myAlreadyAttacked;

	float myYVelocity;
	float myNegYVelocity;
	float myGravity;
	float myStartY;
	float myJumpXDirection;
	bool myStartedJump;

	float myMinX;
	float myMaxX;
	float myJumpCooldown;
	float mySpawnProjectileCooldown;

	bool myAlreadyPlayedSound = false;
};