#pragma once
#include "BaseEnemy.h"


//Simple enemy that patrols back and forth, might try and go for the player later
struct HellCatEntity : public BaseEnemy
{
	StateMachine<HellCatEntity>*  myStateMachine;
	StateMachine<HellCatEntity>*  GetFSM()const { return myStateMachine; }
	HellCatEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo);
	~HellCatEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;
	void HandleDamaged(int damageRecieved) {}
	void HandleMovement();
	void SetAnimation(const std::string& name);
public:

};