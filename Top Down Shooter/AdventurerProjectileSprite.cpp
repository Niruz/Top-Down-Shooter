#include "AdventurerProjectileSprite.h"

AdventurerProjectileSprite::AdventurerProjectileSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["AdventurerProjectile"] = new Animation(3, 0, 34, 9, 102, 9, 0, 0);

}
AdventurerProjectileSprite::~AdventurerProjectileSprite()
{

}