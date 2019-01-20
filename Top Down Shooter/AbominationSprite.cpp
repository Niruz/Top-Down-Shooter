#include "AbominationSprite.h"

AbominationSprite::AbominationSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["AbominationIdle"]             = new Animation(6, 0,  180, 180, 8640, 180, 0, 0, 6);
	myAnimations["AbominationAttack"]           = new Animation(15, 6, 180, 180, 8640, 180, 0, 0, 6);
	myAnimations["AbominationRun"]              = new Animation(8, 24, 180, 180, 8640, 180, 0, 0, 6);
	myAnimations["AbominationHurt"]             = new Animation(3, 33, 180, 180, 8640, 180, 0, 0, 6);
	myAnimations["AbominationDie"]              = new Animation(9, 36, 180, 180, 8640, 180, 0, 0, 6);
	myAnimations["AbominationSpawnProjectile"]  = new Animation(3, 11, 180, 180, 8640, 180, 0, 0, 14);
	myAnimations["AbominationJump"]             = new Animation(4, 10, 180, 180, 8640, 180, 0, 0, 10);
	myAnimations["AbominationLandAttack"]       = new Animation(8, 18, 180, 180, 8640, 180, 0, 0, 10);
}
AbominationSprite::~AbominationSprite()
{

}