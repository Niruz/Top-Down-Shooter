#pragma once
#include "Renderable.h"

class StaticSprite : public Renderable
{
public:
	StaticSprite(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color);
	~StaticSprite();
	inline const VertexArray* getVAO()    const { return myVertexArray; };
	inline const IndexBuffer* getIBO()    const { return myIndexBuffer; };
private:
	VertexArray * myVertexArray;
	IndexBuffer* myIndexBuffer;
};