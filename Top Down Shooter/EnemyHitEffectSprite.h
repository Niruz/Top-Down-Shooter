#pragma once
#include "AnimatedSprite.h"

class EnemyHitEffectSprite : public AnimatedSprite
{
public:
	EnemyHitEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~EnemyHitEffectSprite();

private:
};