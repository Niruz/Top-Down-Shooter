#include "DemonSprite.h"

DemonSprite::DemonSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["DemonAttack"] = new Animation(11, 0, 240, 192, 2640, 192, 0, 0);
	myAnimations["DemonIdle"] = new Animation(4, 5, 37, 65, 481, 65, 0, 0);
	myAnimations["GhostAttack"] = new Animation(4, 9, 37, 65, 481, 65, 0, 0);

}
DemonSprite::~DemonSprite()
{

}