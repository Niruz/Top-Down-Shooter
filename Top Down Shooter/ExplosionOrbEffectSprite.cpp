#include "ExplosionOrbEffectSprite.h"

ExplosionOrbEffectSprite::ExplosionOrbEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["ExplosionOrb"] = new Animation(39, 0, 99.875, 100, 3995, 100, 0, 0, 1);
}
ExplosionOrbEffectSprite::~ExplosionOrbEffectSprite()
{

}