#pragma once
#include "AnimatedSprite.h"

class HellCatSprite : public AnimatedSprite
{
public:
	HellCatSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~HellCatSprite();

private:
};