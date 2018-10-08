#pragma once

class IndexBuffer;
class VertexArray;

//TODO: Rename? Mesh = 3D
struct Mesh
{
	Mesh();
	~Mesh();

	IndexBuffer* mIndexBuffer;
	VertexArray* mVertexArray;

	void Bind() const;
	void Unbind() const;

	void Render();
};