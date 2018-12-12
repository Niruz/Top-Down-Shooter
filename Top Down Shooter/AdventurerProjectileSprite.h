#pragma once
#include "AnimatedSprite.h"

class AdventurerProjectileSprite : public AnimatedSprite
{
public:
	AdventurerProjectileSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~AdventurerProjectileSprite();

private:
};