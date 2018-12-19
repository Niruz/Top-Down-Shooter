#pragma once
#include "AnimatedSprite.h"

class SwordHitEffectSprite : public AnimatedSprite
{
public:
	SwordHitEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~SwordHitEffectSprite();

private:
};