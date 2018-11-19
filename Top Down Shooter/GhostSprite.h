#pragma once
#include "AnimatedSprite.h"

class GhostSprite : public AnimatedSprite
{
public:
	GhostSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~GhostSprite();

private:
};