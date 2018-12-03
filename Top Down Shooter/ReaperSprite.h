#pragma once
#include "AnimatedSprite.h"

class ReaperSprite : public AnimatedSprite
{
public:
	ReaperSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~ReaperSprite();

private:
};