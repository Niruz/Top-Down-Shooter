#include "BloodEffectSprite.h"

BloodEffectSprite::BloodEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	//myAnimations["HitEffectBlood"] = new Animation(10, 0, 64, 64, 640, 64, 0, 0, 3);
	myAnimations["HitEffectBlood1"] = new Animation( 9, 0,  32, 32, 1024, 32, 0, 0, 3);
	myAnimations["HitEffectBlood2"] = new Animation( 9, 9,  32, 32, 1024, 32, 0, 0, 3);
	myAnimations["HitEffectBlood3"] = new Animation( 7, 18, 32, 32, 1024, 32, 0, 0, 3);
	myAnimations["HitEffectBlood4"] = new Animation( 7, 25, 32, 32, 1024, 32, 0, 0, 3);
}
BloodEffectSprite::~BloodEffectSprite()
{

}