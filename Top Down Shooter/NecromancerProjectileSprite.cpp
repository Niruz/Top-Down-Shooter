#include "NecromancerProjectileSprite.h"

NecromancerProjectileSprite::NecromancerProjectileSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["NecromancerProjectile"] = new Animation(3, 0, 34, 9, 102, 9, 0, 0);

}
NecromancerProjectileSprite::~NecromancerProjectileSprite()
{

}