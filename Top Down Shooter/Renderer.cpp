#include "Renderer.h"
#include "ShaderManager.h"
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
void Renderer::Submit(const Renderable* renderable)
{
	myRenderQueue.push_back(renderable);
}

void Renderer::Flush()
{
	while(!myRenderQueue.empty())
	{
		const Renderable* renderable = myRenderQueue.front();

		ShaderMan->bindShader(SIMPLE_FORWARD_SHADER);
		renderable->getVAO()->bind();
		renderable->getIBO()->bind();

		
		glm::mat4 translationMatrix = glm::mat4(1.0f);
		translationMatrix = glm::translate(translationMatrix, renderable->GetPosition());
		glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);

		ShaderMan->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, ortho);
		ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, translationMatrix);
		glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		renderable->getIBO()->unbind();
		renderable->getVAO()->unbind();
		ShaderMan->unbindShader();

		myRenderQueue.pop_front();
	}
}