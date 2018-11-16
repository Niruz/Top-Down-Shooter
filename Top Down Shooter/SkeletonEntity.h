#pragma once
#include "Entity.h"
#include "StateMachine.h"
class TileMap;
class SkeletonSprite;


struct SkeletonEntity : public Entity
{

	StateMachine<SkeletonEntity>*  myStateMachine;
	StateMachine<SkeletonEntity>*  GetFSM()const { return myStateMachine; }

	SkeletonEntity(int id, const std::string& name);
	~SkeletonEntity();

	SkeletonSprite* myAnimatedSprite;

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();

	TileMap* myTileMap;

};


