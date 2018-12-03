#pragma once
#include "BaseEnemy.h"


//Simple enemy that patrols back and forth, might try and go for the player later
struct SkeletonEntity : public BaseEnemy
{
	StateMachine<SkeletonEntity>*  myStateMachine;
	StateMachine<SkeletonEntity>*  GetFSM()const { return myStateMachine; }
	SkeletonEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~SkeletonEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;
	void HandleDamaged(int damageRecieved) {}
	void HandleMovement();
	void SetAnimation(const std::string& name);
public:

};


