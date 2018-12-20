#include "AdventurerSlideEffectSprite.h"

AdventurerSlideEffectSprite::AdventurerSlideEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["AdventurerSlideEffect"] = new Animation(1, 0, 50, 37, 50, 37, 0, 1);
}
AdventurerSlideEffectSprite::~AdventurerSlideEffectSprite()
{

}