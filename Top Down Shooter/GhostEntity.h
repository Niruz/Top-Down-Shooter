#pragma once
#include "BaseEnemy.h"
//Simple enemy that patrols back and forth, might try and go for the player later
struct GhostEntity : public BaseEnemy
{
	StateMachine<GhostEntity>*  myStateMachine;
	StateMachine<GhostEntity>*  GetFSM()const { return myStateMachine; }
	GhostEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~GhostEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();

	void SetAnimation(const std::string& name);
	void ResetAttackTimer();
	void HandleDamaged(int damageRecieved) {}
	bool myAtTarget;
	AnimatedSprite* myPlasmaSprite;
public:

};


