#include "EarthProjectileSprite.h"

EarthProjectileSprite::EarthProjectileSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["EarthProjectile"]     = new Animation(1, 0, 16, 64, 128, 64, 0, 0);
	myAnimations["EarthProjectileLand"] = new Animation(2, 4, 16, 64, 128, 64, 0, 0);

}
EarthProjectileSprite::~EarthProjectileSprite()
{

}