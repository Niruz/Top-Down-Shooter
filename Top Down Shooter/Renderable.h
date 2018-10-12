#pragma once
#include "glm\glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct VertexData
{
	glm::vec3 vertex;
	//glm::vec4 color;
	unsigned int color;
};

class Renderable
{
protected:
	glm::vec3 myPosition;
	glm::vec2 mySize;
	glm::vec4 myColor;



public:

	Renderable(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		: myPosition(position), mySize(size), myColor(color)
	{

	}
	virtual ~Renderable()
	{
		
	}
public:

	void SetPosition(const glm::vec3& position) { myPosition = position; }
	inline const glm::vec3& GetPosition() const { return myPosition; }
	inline const glm::vec2& GetSize()     const { return mySize; }
	inline const glm::vec4& GetColor()    const { return myColor; }
};