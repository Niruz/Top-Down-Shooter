#pragma once
#include "AnimatedSprite.h"

class AbominationSprite : public AnimatedSprite
{
public:
	AbominationSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~AbominationSprite();

private:
};