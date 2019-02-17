#include "SimpleObject.h"
#include <glm/gtc/matrix_transform.hpp>

void SimpleObject::render(const Camera& camera)
{

	mTranslationMatrix = glm::mat4(1.0f);
	mTranslationMatrix = glm::translate(mTranslationMatrix, mPosition);

	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(16, 16, 16));
	ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mTranslationMatrix * camera.mTranslationMatrix * scaleMatrix);
	mTexture->bind();

	mMesh->render();

	mTexture->unbind();

}