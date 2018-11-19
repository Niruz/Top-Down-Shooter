#include "HeroSprite.h"

HeroSprite::HeroSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["HeroRun"] = new Animation(6, 15, 100, 59, 2100, 59);
	myAnimations["HeroAttack"] = new Animation(5, 0, 100, 59, 2100, 59);
	myAnimations["HeroCrouch"] = new Animation(1, 5, 100, 59, 2100, 59);
	myAnimations["HeroHurt"] = new Animation(1, 6, 100, 59, 2100, 59);
	myAnimations["HeroIdle"] = new Animation(4, 7, 100, 59, 2100, 59);
	myAnimations["HeroJump"] = new Animation(2, 11, 100, 59, 2100, 59);
	myAnimations["HeroFall"] = new Animation(2, 13, 100, 59, 2100, 59);
	//myCurrentAnimation = GetAnimation("HeroIdle");
}
HeroSprite::~HeroSprite()
{
	int shit = 5;
}