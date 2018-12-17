#pragma once
#include "AnimatedSprite.h"

class HitEffectSprite : public AnimatedSprite
{
public:
	HitEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~HitEffectSprite();

private:
};