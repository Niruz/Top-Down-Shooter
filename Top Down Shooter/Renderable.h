#pragma once
#include "glm\glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "RendererBase.h"
#include "Texture.h"

struct VertexData
{
	glm::vec3 vertex;
	glm::vec2 uv;
	float tid;
	unsigned int color;
};

class Renderable
{
protected:
	glm::vec3 myPosition;
	glm::vec2 mySize;
	//glm::vec4 myColor;
	unsigned int myColor;
	std::vector<glm::vec2> myUVs;
	Texture* myTexture;

protected:
	Renderable() : myTexture(nullptr)
	{
		SetUVDefaults();
	}

public:

	Renderable(const glm::vec3& position, const glm::vec2& size, const unsigned int& color)
		: myPosition(position), mySize(size), myColor(color), myTexture(nullptr)
	{
		SetUVDefaults();
	}
	Renderable(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		: myPosition(position), mySize(size), myTexture(nullptr)
	{
		SetColor(color);
		SetUVDefaults();
	}
	virtual ~Renderable()
	{
		
	}

	virtual void Submit(RendererBase* renderer) const 
	{
		renderer->Submit(this);
	}
public:

	void SetColor(unsigned int color) { myColor = color; }
	void SetColor(const glm::vec4& color)
	{

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		myColor = a << 24 | b << 16 | g << 8 | r;
	}
	void SetPosition(const glm::vec3& position) { myPosition = position; }
	inline const glm::vec3& GetPosition()			 const { return myPosition; }
	inline const glm::vec2& GetSize()                const { return mySize; }
	inline const unsigned int GetColor()               const { return myColor; }
	inline const std::vector<glm::vec2>& GetUVs()    const { return myUVs; }
	inline const GLuint GetTID() const { return myTexture ? myTexture->getID() : 0; }
private:
	void SetUVDefaults()
	{
		myUVs.push_back(glm::vec2(0, 0));
		myUVs.push_back(glm::vec2(0, 1));
		myUVs.push_back(glm::vec2(1, 1));
		myUVs.push_back(glm::vec2(1, 0));
	}
};