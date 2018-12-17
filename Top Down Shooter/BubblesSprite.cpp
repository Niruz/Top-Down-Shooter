#include "BubblesSprite.h"

BubblesSprite::BubblesSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["BubblesEffect"] = new Animation(61, 0, 100, 100, 6100, 100, 0, 0, 1);
}
BubblesSprite::~BubblesSprite()
{

}