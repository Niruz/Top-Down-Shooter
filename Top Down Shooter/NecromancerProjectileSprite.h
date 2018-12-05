#pragma once
#include "AnimatedSprite.h"

class NecromancerProjectileSprite : public AnimatedSprite
{
public:
	NecromancerProjectileSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~NecromancerProjectileSprite();

private:
};