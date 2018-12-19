#include "PotionSprite.h"

PotionSprite::PotionSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["PotionMove"] = new Animation(4, 0, 16, 16, 64, 16, 0, 0, 14);
}
PotionSprite::~PotionSprite()
{

}