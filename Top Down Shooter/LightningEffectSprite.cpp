#include "LightningEffectSprite.h"

LightningEffectSprite::LightningEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["Lightning"] = new Animation(39, 0, 375, 375, 15000, 375, 0, 0, 0);
}
LightningEffectSprite::~LightningEffectSprite()
{

}