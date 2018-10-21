#include "Renderer.h"
#include "ShaderManager.h"
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
#include "Static_Sprite.h"
void Renderer::Submit(const Renderable* renderable)
{
	myRenderQueue.push_back((StaticSprite*)renderable);
}

void Renderer::Flush()
{
	while(!myRenderQueue.empty())
	{
		const StaticSprite* sprite = myRenderQueue.front();

		ShaderMan->bindShader(SIMPLE_TEXTURE_SHADER);
		sprite->getVAO()->bind();
		sprite->getIBO()->bind();

		
		glm::mat4 translationMatrix = glm::mat4(1.0f);
		translationMatrix = glm::translate(translationMatrix, glm::vec3(sprite->GetPosition()));
		glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);

		ShaderMan->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, ortho);
		ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, translationMatrix);
		glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		sprite->getIBO()->unbind();
		sprite->getVAO()->unbind();
		ShaderMan->unbindShader();

		myRenderQueue.pop_front();
	}
}