#include "GhostSprite.h"

GhostSprite::GhostSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["GhostDie"] = new Animation(5, 0, 37, 65, 481, 65,0,0);
	myAnimations["GhostPatrol"] = new Animation(4, 5, 37, 65, 481, 65,0,0);
	myAnimations["GhostAttack"] = new Animation(4, 9, 37, 65, 481, 65,0,0);
	
}
GhostSprite::~GhostSprite()
{

}