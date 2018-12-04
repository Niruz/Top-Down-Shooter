#pragma once
#include "AnimatedSprite.h"

class ImpSprite : public AnimatedSprite
{
public:
	ImpSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~ImpSprite();

private:
};