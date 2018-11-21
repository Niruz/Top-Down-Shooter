#include "EyeMonsterSprite.h"

EyeMonsterSprite::EyeMonsterSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["EyeDie"] = new Animation(5, 0, 80, 80, 720, 80,0,0);
	myAnimations["EyePatrol"] = new Animation(4, 5, 80, 80, 720, 80,0,0);

}
EyeMonsterSprite::~EyeMonsterSprite()
{

}