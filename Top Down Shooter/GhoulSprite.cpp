#include "GhoulSprite.h"

GhoulSprite::GhoulSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["GhoulAttack"] = new Animation(5,  0, 51, 20, 1326, 20, 0, 0);
	myAnimations["GhoulDie"] =    new Animation(5,  8, 51, 20, 1326, 20, 0, 0);
	myAnimations["GhoulHurt"] =   new Animation(3, 13, 51, 20, 1326, 20, 0, 0);
	myAnimations["GhoulIdle"] =   new Animation(4, 16, 51, 20, 1326, 20, 0, 0);
	myAnimations["GhoulRun"] =    new Animation(6, 20, 51, 20, 1326, 20, 0, 0);

}
GhoulSprite::~GhoulSprite()
{
}