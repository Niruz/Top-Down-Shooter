#pragma once
#include "AnimatedSprite.h"

class FireGolemSprite : public AnimatedSprite
{
public:
	FireGolemSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~FireGolemSprite();

private:
};