#include "BigSkeletonSprite.h"

BigSkeletonSprite::BigSkeletonSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["SkeletonIdle"]      = new Animation(7,  0,  128, 64, 6144, 64, 0, 0, 6);
	myAnimations["SkeletonAttack"]    = new Animation(17, 7,  128, 64, 6144, 64, 0, 0, 6);
	myAnimations["SkeletonRun"]       = new Animation(10, 24, 128, 64, 6144, 64, 0, 0, 6);
	myAnimations["SkeletonDie"]       = new Animation(12, 34, 128, 64, 6144, 64, 0, 0, 6);
	myAnimations["SkeletonHurt"]      = new Animation(2,  46, 128, 64, 6144, 64, 0, 0, 6);
}
BigSkeletonSprite::~BigSkeletonSprite()
{

}