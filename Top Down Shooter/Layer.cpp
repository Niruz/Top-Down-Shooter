#include "Layer.h"
#include <glm/gtc/matrix_transform.hpp>
Layer::Layer()
{

}
Layer::Layer(RendererBase* renderer, Shader* shader, const glm::mat4& projectionMatrix)
	:myRenderer(renderer), myShader(shader), myProjectionMatrix(projectionMatrix)
{
	myShader->bind();
	myShader->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, myProjectionMatrix);
	myShader->unbind();
	
	/*glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, glm::vec3(20.0f, 0.0, 0.0f));
	myRenderer->Push(translationMatrix);*/
}
Layer::~Layer()
{
	delete myRenderer;
	for (Renderable* renderable : myRenderables)
		delete renderable;
}
void Layer::Add(Renderable* renderable)
{
	myRenderables.push_back(renderable);
}
void Layer::Render()
{
	myShader->bind();

	myRenderer->Begin();
	int i = 0;
	for (Renderable * renderable : myRenderables)
	{
		//just an example usage
		/*if(i % 2 == 0)
		{
			glm::mat4 translationMatrix = glm::mat4(1.0f);
			translationMatrix = glm::translate(translationMatrix, glm::vec3(10.0f, 10.0, 0.0f));
			myRenderer->Push(translationMatrix); 
			myRenderer->Submit(renderable);
			myRenderer->Pop();
		}
		else
		{
			myRenderer->Submit(renderable);
		}
		i++;
		*/
		myRenderer->Submit(renderable);
	}
		
	myRenderer->End();
	myRenderer->Flush();

	myShader->unbind();
}