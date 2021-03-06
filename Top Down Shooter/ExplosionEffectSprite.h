#pragma once
#include "AnimatedSprite.h"

class ExplosionEffectSprite : public AnimatedSprite
{
public:
	ExplosionEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~ExplosionEffectSprite();

private:
};