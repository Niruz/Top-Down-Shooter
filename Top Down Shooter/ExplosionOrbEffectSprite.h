#pragma once
#include "AnimatedSprite.h"

class ExplosionOrbEffectSprite : public AnimatedSprite
{
public:
	ExplosionOrbEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~ExplosionOrbEffectSprite();

private:
};