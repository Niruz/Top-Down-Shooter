#include "SkeletonSprite.h"

SkeletonSprite::SkeletonSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["SkeletonWalk"] = new Animation(8, 0, 44, 52, 616, 52,0,0);
	myAnimations["SkeletonRise"] = new Animation(6, 8, 44, 52, 616, 52,0,0);

}
SkeletonSprite::~SkeletonSprite()
{
	
}