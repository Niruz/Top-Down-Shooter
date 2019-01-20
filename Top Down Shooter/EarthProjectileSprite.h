#pragma once
#include "AnimatedSprite.h"

class EarthProjectileSprite : public AnimatedSprite
{
public:
	EarthProjectileSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~EarthProjectileSprite();

private:
};