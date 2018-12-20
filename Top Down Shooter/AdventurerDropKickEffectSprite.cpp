#include "AdventurerDropKickEffectSprite.h"

AdventurerDropKickEffectSprite::AdventurerDropKickEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: AnimatedSprite(position, size, texture, heading)
{
	myAnimations["AdventurerDropKickEffect"] = new Animation(1, 0, 50, 37, 50, 37, 0, 1);
}
AdventurerDropKickEffectSprite::~AdventurerDropKickEffectSprite()
{

}