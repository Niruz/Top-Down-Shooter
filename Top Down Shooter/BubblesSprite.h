#pragma once
#include "AnimatedSprite.h"

class BubblesSprite : public AnimatedSprite
{
public:
	BubblesSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~BubblesSprite();

private:
};