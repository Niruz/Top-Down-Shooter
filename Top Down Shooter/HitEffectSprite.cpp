#include "HitEffectSprite.h"

HitEffectSprite::HitEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["HitEffectSlow"] = new Animation(36, 0, 100, 100, 3600, 100, 0, 0, 1);
	myAnimations["HitEffect"] = new Animation(18, 0, 100, 100, 1800, 100, 0, 0, 1);
}
HitEffectSprite::~HitEffectSprite()
{

}