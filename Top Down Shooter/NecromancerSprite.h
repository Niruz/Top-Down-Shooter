#pragma once
#include "AnimatedSprite.h"

class NecromancerSprite : public AnimatedSprite
{
public:
	NecromancerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~NecromancerSprite();

private:
};