#include "ImpSprite.h"

ImpSprite::ImpSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["ImpAttack"] = new Animation(10, 0, 50, 50, 1650, 50, 0, 0);
	myAnimations["ImpDie"] = new Animation(10, 10, 50, 50, 1650, 50, 0, 0);
	myAnimations["ImpHurt"] = new Animation(3, 20, 50, 50, 1650, 50, 0, 0);
	myAnimations["ImpIdle"] = new Animation(5, 23, 50, 50, 1650, 50, 0, 0);
	myAnimations["ImpRun"] = new Animation(5, 28, 50, 50, 1650, 50, 0, 0);

}
ImpSprite::~ImpSprite()
{
}