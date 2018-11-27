#include "DemonSprite.h"

DemonSprite::DemonSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["DemonWindUp"] = new Animation(7, 0, 240, 192, 2640, 192, 0, 0);
	myAnimations["DemonAttack"] = new Animation(3, 7, 240, 192, 2640, 192, 0, 0);
	myAnimations["DemonWindDown"] = new Animation(4, 7, 240, 192, 2640, 192, 0, 0);
	myAnimations["DemonIdle"] = new Animation(6, 0, 160, 144, 960, 144, 0, 0);

}
DemonSprite::~DemonSprite()
{

}