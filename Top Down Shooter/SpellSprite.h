#pragma once
#include "AnimatedSprite.h"

class SpellSprite : public AnimatedSprite
{
public:
	SpellSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~SpellSprite();

private:
};