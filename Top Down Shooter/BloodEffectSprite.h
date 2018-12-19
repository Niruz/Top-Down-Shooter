#pragma once
#include "AnimatedSprite.h"

class BloodEffectSprite : public AnimatedSprite
{
public:
	BloodEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~BloodEffectSprite();

private:
};