#pragma once
#include "Renderable.h"

class Sprite : public Renderable
{
public:
	Sprite(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color);
	Sprite::Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture);
	~Sprite();
private:

};