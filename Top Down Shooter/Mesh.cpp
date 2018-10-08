#include "Mesh.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

Mesh::Mesh()
{

}
Mesh::~Mesh()
{
	delete mVertexArray;
	delete mIndexBuffer;
}
void Mesh::Bind() const
{

}
void Mesh::Unbind() const
{

}
void Mesh::Render()
{
	//glDrawElements(GL_TRIANGLES,mVertexArray->myc)
}