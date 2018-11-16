#pragma once
#include "AnimatedSprite.h"

class SkeletonSprite : public AnimatedSprite
{
public:
	SkeletonSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~SkeletonSprite();

private:
};