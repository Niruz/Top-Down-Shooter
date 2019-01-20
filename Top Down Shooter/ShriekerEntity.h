#pragma once
#include "BaseEnemy.h"
#include "TileMap.h"
class ShakeInfo;
//Simple enemy that prols back and forth, might try and go for the player later
struct ShriekerEntity : public BaseEnemy
{
	StateMachine<ShriekerEntity>*  myStateMachine;
	StateMachine<ShriekerEntity>*  GetFSM()const { return myStateMachine; }
	ShriekerEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~ShriekerEntity();

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

	void ChooseAppearPoint();

	void AddAppearPoint(const glm::vec2& point);
public:

	std::vector<glm::vec2> myAppearPoints;
	int myCurrentAppearIndex;
	//Bad design...
	TileMap * myTileMap;
	ShakeInfo* myShakeInfoSlamAttack;
	float myAttackCooldown;
	bool myAlreadyAttacked;
};