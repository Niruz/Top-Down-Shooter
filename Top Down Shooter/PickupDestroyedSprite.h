#pragma once
#include "AnimatedSprite.h"

class PickupDestroyedSprite : public AnimatedSprite
{
public:
	PickupDestroyedSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~PickupDestroyedSprite();

private:
};