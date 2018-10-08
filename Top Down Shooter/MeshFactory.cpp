#include "MeshFactory.h"
#include "Mesh.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

Mesh* MeshFactory::createQuad(float size)
{
	GLfloat vertices[] =
	{
		-1.0*size, 0.0, -1.0*size, //0 
		1.0*size, 0.0, -1.0*size,// 1
		1.0*size, 0.0, 1.0*size,  // 2
		-1.0*size, 0.0, 1.0*size // 3
	};

	GLfloat normals[] =
	{
		0.0, 1.0, 0.0
	};

	GLushort indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	GLfloat texCoords[] =
	{
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0
	};

	VertexArray* buffer = new VertexArray();

	buffer->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	buffer->addBuffer(new Buffer(normals, 3, 3), 1);
	buffer->addBuffer(new Buffer(texCoords, 4 * 2, 2), 2);

	//	unsigned short indices[6 * 6 * 3];
	//for (unsigned int i = 0; i < (6 * 6 * 3); ++i)
	//indices[i] = i;

	IndexBuffer* indexBuffer = new IndexBuffer(indices, 6);

	return new Mesh(buffer, indexBuffer);
}
Mesh* MeshFactory::createSphere(float radius, unsigned int rings, unsigned int sectors)
{
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;

	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	vertices.resize(rings * sectors * 3);
	normals.resize(rings * sectors * 3);
	texcoords.resize(rings * sectors * 2);
	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator n = normals.begin();
	std::vector<GLfloat>::iterator t = texcoords.begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		float const y = sin(-M_PI_2 + M_PI * r * R);
		float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

		*t++ = s * S;
		*t++ = r * R;

		*v++ = x * radius;
		*v++ = y * radius;
		*v++ = z * radius;

		*n++ = x;
		*n++ = y;
		*n++ = z;
	}

	indices.resize(rings * sectors * 6);
	std::vector<GLushort>::iterator i = indices.begin();
	for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
		/**i++ = r * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;*/

		*i++ = r * sectors + s; // 0
		*i++ = r * sectors + (s + 1); // 1
		*i++ = (r + 1) * sectors + (s + 1); // 2
		*i++ = (r + 1) * sectors + (s + 1); // 2
		*i++ = (r + 1) * sectors + s; // 3
		*i++ = r * sectors + s; // 0
	}

	VertexArray* buffer = new VertexArray();

	buffer->addBuffer(new Buffer(&vertices[0], vertices.size(), 3), 0);
	buffer->addBuffer(new Buffer(&normals[0], normals.size(), 3), 1);

	//	unsigned short indices[6 * 6 * 3];
	//for (unsigned int i = 0; i < (6 * 6 * 3); ++i)
	//indices[i] = i;

	IndexBuffer* indexBuffer = new IndexBuffer(&indices[0], indices.size());

	return new Mesh(buffer, indexBuffer);
}
Mesh* MeshFactory::createCube(float size)
{

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f
	};

	GLfloat normals[] =
	{
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};



	VertexArray* buffer = new VertexArray();

	buffer->addBuffer(new Buffer(vertices, 6 * 6 * 3, 3), 0);
	buffer->addBuffer(new Buffer(normals, 6 * 6 * 3, 3), 1);

	unsigned short indices[6 * 6 * 3];
	for (unsigned int i = 0; i < (6 * 6 * 3); ++i)
		indices[i] = i;

	IndexBuffer* indexBuffer = new IndexBuffer(indices, 6 * 6 * 3);

	return new Mesh(buffer, indexBuffer);
}

Mesh* MeshFactory::createCube()
{
	GLfloat vertices[] =
	{
		-1.0, -1.0, 0.0, //0 
		1.0, -1.0, 0.0, // 1
		1.0, 1.0, 0.0,  // 2
		-1.0, 1.0, 0.0 // 3
	};

	GLfloat normals[] =
	{
		0.0, 1.0, 0.0
	};

	/*	GLfloat texCoords[] =
	{
	0.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0
	};*/

	GLfloat texCoords[] =
	{
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};

	GLushort indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	VertexArray* buffer = new VertexArray();

	buffer->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	buffer->addBuffer(new Buffer(normals, 3, 3), 1);
	buffer->addBuffer(new Buffer(texCoords, 4 * 2, 2), 2);
	//	unsigned short indices[6 * 6 * 3];
	//for (unsigned int i = 0; i < (6 * 6 * 3); ++i)
	//indices[i] = i;

	IndexBuffer* indexBuffer = new IndexBuffer(indices, 6);

	return new Mesh(buffer, indexBuffer);
}
Mesh* MeshFactory::createCircle(float radius)
{
	std::vector<GLfloat> vertices;
	std::vector<GLushort> indices;

	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	for (int i = 0; i <= 360; i += 10)
	{
		float radians = i * M_PI / 180;
		float x = radius * cos((float)radians);
		float y = radius * sin((float)radians);




		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);

		/*	radians = (i + 10) * M_PI / 180;
		x = radius * cos((float)radians);
		y = radius * sin((float)radians);

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);*/


		//vertices.push_back

		//	glVertex3f(x, y, 0);
	}
	for (unsigned int i = 1; i < vertices.size(); i++)
	{
		indices.push_back(0);
		indices.push_back(i);

		indices.push_back(i + 1);
	}

	VertexArray* buffer = new VertexArray();

	buffer->addBuffer(new Buffer(&vertices[0], vertices.size(), 3), 0);

	//	unsigned short indices[6 * 6 * 3];
	//for (unsigned int i = 0; i < (6 * 6 * 3); ++i)
	//indices[i] = i;

	IndexBuffer* indexBuffer = new IndexBuffer(&indices[0], indices.size());

	return new Mesh(buffer, indexBuffer);
}
Mesh* MeshFactory::createTriangle()
{
	GLfloat vertices[] =
	{
		-1.0, -1.0, 0.0, //0 
		0.0, 1.0, 0.0, // 1
		1.0, -1.0, 0.0,  // 2
	};

	/*	GLfloat normals[] =
	{
	0.0, 1.0, 0.0
	};*/

	GLushort indices[] =
	{
		0, 1, 2
	};

	VertexArray* buffer = new VertexArray();

	buffer->addBuffer(new Buffer(vertices, 3 * 3, 3), 0);
	//	buffer->addBuffer(new Buffer(normals, 3, 3), 1);

	//	unsigned short indices[6 * 6 * 3];
	//for (unsigned int i = 0; i < (6 * 6 * 3); ++i)
	//indices[i] = i;

	IndexBuffer* indexBuffer = new IndexBuffer(indices, 6);

	return new Mesh(buffer, indexBuffer);
}

