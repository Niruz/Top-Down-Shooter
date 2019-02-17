#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "ShaderManager.h"
#include "Camera.h"
struct SimpleObject
{

	Mesh* mMesh;
	Texture* mTexture;

	glm::mat4 mTranslationMatrix;
	glm::vec3 mPosition;

	void setPosition(const glm::vec3& pos) { mPosition = pos; };


	void render(const Camera& camera);
};