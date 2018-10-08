#pragma once

#define MeshFact MeshFactory::Instance()

class Mesh;
class MeshFactory
{
public:

	static MeshFactory* Instance();

	Mesh* CreateQuad();

private:

	MeshFactory() {};
	MeshFactory(const MeshFactory&);
	MeshFactory& operator = (const MeshFactory&);
	~MeshFactory() {};
};