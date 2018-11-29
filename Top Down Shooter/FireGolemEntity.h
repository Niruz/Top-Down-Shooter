#pragma once
#include "BaseEnemy.h"


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
public:

};