#pragma once
#include "AnimatedSprite.h"

class ImpProjectileSprite : public AnimatedSprite
{
public:
	ImpProjectileSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~ImpProjectileSprite();

private:
};