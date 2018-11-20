#include "HellCatSprite.h"

HellCatSprite::HellCatSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["HellCatDie"] = new Animation(5, 0, 96, 53, 864, 53);
	myAnimations["HellCatPatrol"] = new Animation(4, 5, 96, 53, 864, 53);

}
HellCatSprite::~HellCatSprite()
{

}