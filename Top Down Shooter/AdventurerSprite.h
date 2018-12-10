#pragma once
#include "AnimatedSprite.h"

class AdventurerSprite : public AnimatedSprite
{
public:
	AdventurerSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~AdventurerSprite();

private:
};