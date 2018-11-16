#include "SkeletonEntity.h"

SkeletonEntity::SkeletonEntity(int id, const std::string& name): 
	Entity(id, name)
{

}
SkeletonEntity::~SkeletonEntity()
{

}
void SkeletonEntity::Update() 
{

}
bool SkeletonEntity::HandleMessage(const Message& msg)
{
	return false;
}
void SkeletonEntity::HandleMovement()
{

}
