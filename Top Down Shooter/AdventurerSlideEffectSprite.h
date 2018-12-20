#pragma once
#include "AnimatedSprite.h"

class AdventurerSlideEffectSprite : public AnimatedSprite
{
public:
	AdventurerSlideEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~AdventurerSlideEffectSprite();

private:
};