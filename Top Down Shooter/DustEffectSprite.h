#pragma once
#include "AnimatedSprite.h"

class DustEffectSprite : public AnimatedSprite
{
public:
	DustEffectSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~DustEffectSprite();

private:
};