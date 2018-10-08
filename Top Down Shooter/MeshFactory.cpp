#include "MeshFactory.h"
#include "Mesh.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

MeshFactory* MeshFactory::Instance()
{
	static MeshFactory instance;
	return &instance;
}
Mesh* MeshFactory::CreateQuad()
{
	float vertices[]  =
	{
		-1.0f, -1.0f, 0.0f,  //bottom left
		1.0f, -1.0f, 0.0f,  //bottom right
		-1.0f,  1.0f, 0.0f,  //top left
		 1.0f,  1.0f, 0.0f, //top right
		 
	};

	unsigned int indices[] = 
	{
		0,1,3,
		0,3,2
	};

	Buffer* buffy = new Buffer(vertices,4*3, 3);
	IndexBuffer* ib = new IndexBuffer(indices,2*3);
	VertexArray* va = new VertexArray();
	va->addBuffer(buffy,0);

	Mesh* temp = new Mesh;
	temp->mIndexBuffer = ib;
	temp->mVertexArray = va;
	return temp;
}