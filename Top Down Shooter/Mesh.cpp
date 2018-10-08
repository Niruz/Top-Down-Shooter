#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer)
	: mVertexArray(vertexArray), mIndexBuffer(indexBuffer)
{

}
void Mesh::render()
{
	getVAO()->bind();
	getIBO()->bind();

	glDrawElements(GL_TRIANGLES, getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

	getIBO()->unbind();
	getVAO()->unbind();
}
const VertexArray* Mesh::getVAO() const
{
	 return mVertexArray; 
}
const IndexBuffer* Mesh::getIBO() const
{
	return mIndexBuffer;
}