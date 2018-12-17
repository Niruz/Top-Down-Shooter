#include "SpellSprite.h"

SpellSprite::SpellSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["SpellEffect"] = new Animation(74, 0, 100, 100, 7400, 100, 0, 0, 1);
}
SpellSprite::~SpellSprite()
{

}