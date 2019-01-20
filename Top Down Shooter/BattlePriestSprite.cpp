#include "BattlePriestSprite.h"

BattlePriestSprite::BattlePriestSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["BattlePriestIdle"]           = new Animation(12, 0,  99.83, 100, 5990, 100, 0, 0, 8);
	myAnimations["BattlePriestRun"]            = new Animation(10,12,  99.83, 100, 5990, 100, 0, 0, 8);
	myAnimations["BattlePriestAttack"]         = new Animation(17,22,  99.83, 100, 5990, 100, 0, 0, 8);
	myAnimations["BattlePriestHurt"]           = new Animation(3, 39,  99.83, 100, 5990, 100, 0, 0, 8);
	myAnimations["BattlePriestDeath"]          = new Animation(10, 42, 99.83, 100, 5990, 100, 0, 0, 8);
}
BattlePriestSprite::~BattlePriestSprite()
{

}