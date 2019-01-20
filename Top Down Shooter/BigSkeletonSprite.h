#pragma once
#include "AnimatedSprite.h"

class BigSkeletonSprite : public AnimatedSprite
{
public:
	BigSkeletonSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~BigSkeletonSprite();

private:
};