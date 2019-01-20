#include "DustEffectSprite.h"

DustEffectSprite::DustEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["Dust"] = new Animation(60, 0, 227.272727, 227, 15000, 227, 0, 0, 1);
}
DustEffectSprite::~DustEffectSprite()
{

}