#pragma once

#include "Entity.h"
#include "Camera.h"
#include "StateMachine.h"

#include "AABB.h"
class TileMap;
class Group;
class HeroSprite;
class AdventurerSprite;
class Sprite;
class ShakeInfo;

enum StateTest
{
	RUNNING,
	IDLE,
	CROUCH,
	ATTACKING
};


//Test to see how complex the states will be

struct HeroEntity : public Entity
{

	StateMachine<HeroEntity>*  myStateMachine;
	StateMachine<HeroEntity>*  GetFSM()const { return myStateMachine; }

	HeroEntity(int id, const std::string& name);
	~HeroEntity();

	Group* mySprite;
	AdventurerSprite* myAnimatedSprite;

	
	void Update() override;
	bool HandleMessage(const Message& msg) override;


	void UpdateTransformationMatrix(const Camera& camera);

	void setDirection(const glm::vec2& direction);
	void processKeyBoard(int key, float deltaTime, int action);
	float map(float s, float a1, float a2, float b1, float b2);
	void SetAnimation(const std::string& name);
	glm::vec3 mPosition;
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 modelMatrix;

	glm::vec3 myDirection;


	float myPosXDirection;
	float myPosYDirection;
	float myNegXDirection;
	float myNegYDirection;
	float myYVelocity;
	float myGravity;

	void HandleMovement();
	void HandleGravity();
	void HandleJump();
	void HandleDamaged(int damageRecieved);
	void StartJump();
	void CheckIfFalling();
	bool IsOnSpikes();
	bool inAir;
	void Respawn();
	float mAngle;

	int currentKeyInput;
	float myStartJumpTime;

	TileMap* myTileMap;
	Sprite* myPlayerAABB;
	AABB* myAABB;
	StateTest myState;

	Sprite* mySwordSpriteAABB;
	AABB* mySwordAABB;
	float mySwordAABBRightX;
	float mySwordAABBLeftX;

	int myHealth;
	int myDamageFrameCounter;
	bool myIsDamaged;
	bool basicAttack;
	ShakeInfo* myShakeInfoBasicAttack;

	bool myShouldEnterNextSwordAttack;
	float myCurrentSwordAttackCooldownTimer;

	float myStartDeadTimer;
};


