#pragma once
#include "Renderable.h"

class Sprite : public Renderable
{
public:
	Sprite(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color);
	//If we want single textures
	Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture);
	//If we want them from an atlas
	Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, const glm::vec2& atlasposition);
	~Sprite();
private:

};