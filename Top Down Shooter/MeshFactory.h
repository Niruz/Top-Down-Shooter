#pragma once


class Mesh;
class MeshFactory
{
public:

	static Mesh* createCube(float size);
	static Mesh* createQuad(float size);
	static Mesh* createSphere(float radius, unsigned int rings, unsigned int sectors);

	static Mesh* createCube();
	static Mesh* createCircle(float radius);
	static Mesh* createTriangle();

};
