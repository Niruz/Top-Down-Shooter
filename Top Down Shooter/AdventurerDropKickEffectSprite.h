#pragma once
#include "AnimatedSprite.h"

class AdventurerDropKickEffectSprite : public AnimatedSprite
{
public:
	AdventurerDropKickEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~AdventurerDropKickEffectSprite();

private:
};