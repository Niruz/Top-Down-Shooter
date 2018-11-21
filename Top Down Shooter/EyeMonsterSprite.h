#pragma once
#include "AnimatedSprite.h"

class EyeMonsterSprite : public AnimatedSprite
{
public:
	EyeMonsterSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);
	virtual ~EyeMonsterSprite();

private:
};