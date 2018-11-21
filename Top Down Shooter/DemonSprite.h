#pragma once
#include "AnimatedSprite.h"

class DemonSprite : public AnimatedSprite
{
public:
	DemonSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~DemonSprite();

private:
};