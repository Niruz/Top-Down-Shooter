#pragma once
#include "AnimatedSprite.h"

class BattlePriestSprite : public AnimatedSprite
{
public:
	BattlePriestSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~BattlePriestSprite();

private:
};