#pragma once
#include "AnimatedSprite.h"

class GhoulSprite : public AnimatedSprite
{
public:
	GhoulSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~GhoulSprite();

private:
};