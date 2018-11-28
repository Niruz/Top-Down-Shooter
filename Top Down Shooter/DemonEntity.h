#pragma once
#include "BaseEnemy.h"


//Simple enemy that patrols back and forth, might try and go for the player later
struct DemonEntity : public BaseEnemy
{
	StateMachine<DemonEntity>*  myStateMachine;
	StateMachine<DemonEntity>*  GetFSM()const { return myStateMachine; }
	DemonEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~DemonEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();
	void SetAnimation(const std::string& name);
	void ResetAttackTimer();
public:

	float myStartTime;
	bool setonce;
	bool breatheFire;
	float storedY;
};
