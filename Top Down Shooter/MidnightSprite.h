#pragma once
#include "AnimatedSprite.h"

class MidnightSprite : public AnimatedSprite
{
public:
	MidnightSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~MidnightSprite();

private:
};