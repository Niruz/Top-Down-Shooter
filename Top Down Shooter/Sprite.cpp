#include "Sprite.h"
Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	:Renderable(position,size,color)
{

}
Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, Texture* texture)
	: Renderable(position, size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	myTexture = texture;
}
Sprite::~Sprite() 
{

}