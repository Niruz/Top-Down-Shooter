#pragma once
#include "glm\glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct VertexData
{
	glm::vec3 vertex;
	glm::vec4 color;

};

class Renderable
{
protected:
	glm::vec3 myPosition;
	glm::vec2 mySize;
	glm::vec4 myColor;

	VertexArray* myVertexArray;
	IndexBuffer* myIndexBuffer;

public:

	Renderable(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		: myPosition(position), mySize(size), myColor(color)
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

		myVertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		myVertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0	};
		myIndexBuffer = new IndexBuffer(indices, 6);
	}
	virtual ~Renderable()
	{
		delete myVertexArray;
		delete myIndexBuffer;
	}
public:
	inline const VertexArray* getVAO()    const { return myVertexArray; };
	inline const IndexBuffer* getIBO()    const { return myIndexBuffer; };
	inline const glm::vec3& GetPosition() const { return myPosition; }
	inline const glm::vec2& GetSize()     const { return mySize; }
	inline const glm::vec4& GetColor()    const { return myColor; }
};