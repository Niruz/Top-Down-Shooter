#pragma once
#include "AnimatedSprite.h"

class LightningEffectSprite : public AnimatedSprite
{
public:
	LightningEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~LightningEffectSprite();

private:
};