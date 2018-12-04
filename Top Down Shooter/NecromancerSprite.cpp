#include "NecromancerSprite.h"

NecromancerSprite::NecromancerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["NecromancerAttack"]    = new Animation(6, 0,  102, 61,  3570, 61, 0, 0);
	myAnimations["NecromancerDie"]       = new Animation(10, 6,  102, 61,  3570, 61, 0, 0);
	myAnimations["NecromancerHurt"]      = new Animation(3, 16, 102, 61,  3570, 61, 0, 0);
	myAnimations["NecromancerIdle"]      = new Animation(4, 19,  102, 61,  3570, 61, 0, 0);
	myAnimations["NecromancerRun"]       = new Animation(6, 23,  102, 61,  3570, 61, 0, 0);
	myAnimations["NecromancerSummon"]    = new Animation(6, 29,  102, 61,  3570, 61, 0, 0);

}
NecromancerSprite::~NecromancerSprite()
{

}