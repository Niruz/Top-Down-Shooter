#pragma once
#include "AnimatedSprite.h"

class PotionSprite : public AnimatedSprite
{
public:
	PotionSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~PotionSprite();

private:
};