#pragma once
#include "AnimatedSprite.h"

class PlasmaSprite : public AnimatedSprite
{
public:
	PlasmaSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~PlasmaSprite();

private:
};