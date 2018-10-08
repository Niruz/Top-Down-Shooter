#include "SimpleObject.h"
#include <glm/gtc/matrix_transform.hpp>

void SimpleObject::render(const Camera& camera)
{

	mTranslationMatrix = glm::mat4(1.0f);
	mTranslationMatrix = glm::translate(mTranslationMatrix, mPosition);
	ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mTranslationMatrix * camera.mTranslationMatrix);
	mTexture->bind();

	mMesh->render();

	mTexture->unbind();

}