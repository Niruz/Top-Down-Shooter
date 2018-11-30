#pragma once
#include "BaseEnemy.h"
#include "TileMap.h"
class ShakeInfo;
//Simple enemy that patrols back and forth, might try and go for the player later
struct FireGolemEntity : public BaseEnemy
{
	StateMachine<FireGolemEntity>*  myStateMachine;
	StateMachine<FireGolemEntity>*  GetFSM()const { return myStateMachine; }
	FireGolemEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~FireGolemEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();
	void SetAnimation(const std::string& name);

	void ResetAttackTimer();
	void SetFacing();

	bool FirstTimeSeeingPlayer();
	bool IsPlayerWithinPatrolRange();
	bool IsPlayerWithinAttackDistance();
	bool AmIWithinMyPatrolDistance();
	bool IsPlayerToTheRight();
	bool IsAttackCoolDownReady();
public:
	bool shakeAttack1;
	bool shakeAttack2;
	ShakeInfo* myShakeInfoBasicAttack;
	ShakeInfo* myShakeInfoSlamAttack;
	bool firstTimeSeeingPlayer;

	//Bad design...
	TileMap* myTileMap;

	float myAttackCooldown;
};