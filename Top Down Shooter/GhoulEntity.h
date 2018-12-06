#pragma once
#include "BaseEnemy.h"
#include "TileMap.h"
class ShakeInfo;
//Simple enemy that patrols back and forth, might try and go for the player later
struct GhoulEntity : public BaseEnemy
{
	StateMachine<GhoulEntity>*  myStateMachine;
	StateMachine<GhoulEntity>*  GetFSM()const { return myStateMachine; }
	GhoulEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~GhoulEntity();

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
	TileMap* myTileMap;

	float myAttackCooldown;
	bool myAlreadyAttacked;
};