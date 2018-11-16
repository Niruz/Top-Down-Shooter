#pragma once
#include "AnimatedSprite.h"

class HeroSprite : public AnimatedSprite
{
public:
	HeroSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~HeroSprite();

private:
};