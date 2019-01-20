#pragma once
#include "AnimatedSprite.h"

class ShriekerSprite : public AnimatedSprite
{
public:
	ShriekerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~ShriekerSprite();

private:
};