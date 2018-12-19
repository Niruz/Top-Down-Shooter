#include "PickupDestroyedSprite.h"

PickupDestroyedSprite::PickupDestroyedSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["PickupDestroyed"] = new Animation(5, 0, 16, 16, 80, 16, 0, 0, 5);
}
PickupDestroyedSprite::~PickupDestroyedSprite()
{

}