#include "Static_Sprite.h"

StaticSprite::StaticSprite(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color)
	: Renderable(position, size, color)
{
	myVertexArray = new VertexArray();
	GLfloat vertices[] =
	{
		0, 0, 0,
		0, size.y, 0,
		size.x, size.y, 0,
		size.x, 0, 0
	};

	GLfloat colors[] =
	{
		color.x, color.y, color.z ,color.w,
		color.x, color.y, color.z ,color.w,
		color.x, color.y, color.z ,color.w,
		color.x, color.y, color.z ,color.w
	};

	GLfloat texCoords[] = 
	{
		0, 0,
		0, 1,
		1, 1,
		1, 0,
	};

	myVertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	myVertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
	myVertexArray->addBuffer(new Buffer(texCoords, 4 * 2,2), 2);
	GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
	myIndexBuffer = new IndexBuffer(indices, 6);
}
StaticSprite::~StaticSprite()
{
	delete myVertexArray;
	delete myIndexBuffer;
}