#pragma once
#include "BaseEnemy.h"


//Simple enemy that patrols back and forth, might try and go for the player later
struct EyeMonsterEntity : public BaseEnemy
{
	StateMachine<EyeMonsterEntity>*  myStateMachine;
	StateMachine<EyeMonsterEntity>*  GetFSM()const { return myStateMachine; }
	EyeMonsterEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~EyeMonsterEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();
	void SetAnimation(const std::string& name);
public:

	float angle;
};

