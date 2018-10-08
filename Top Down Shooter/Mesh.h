#pragma once

#include "glm\glm.hpp"

#include "Buffer.h"

class IndexBuffer;
class VertexArray;

class Mesh
{
public:
	Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer);
	~Mesh()
	{
		delete mVertexArray;
		delete mIndexBuffer;
	};


	const VertexArray* getVAO() const; 
	const IndexBuffer* getIBO() const;

	void render();
private:

	VertexArray * mVertexArray;
	IndexBuffer* mIndexBuffer;
};
