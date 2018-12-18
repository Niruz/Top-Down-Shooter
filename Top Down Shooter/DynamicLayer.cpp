#include "DynamicLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderable.h"
DynamicLayer::DynamicLayer()
{

}
DynamicLayer::DynamicLayer(RendererBase* renderer, Shader* shader, const glm::mat4& projectionMatrix)
	: Layer(renderer,shader,projectionMatrix)
{

}
DynamicLayer::~DynamicLayer()
{

}
void DynamicLayer::Render()
{
	myShader->bind();

	myRenderer->Begin();

	std::vector<Renderable*>::iterator it = myRenderables.begin();

	while (it != myRenderables.end()) 
	{

		if ((*it)->myMarkedForDeletion)
		{

			it = myRenderables.erase(it);
		}
		else
		{
			(*it)->Submit(myRenderer);
			++it;
		}
			
	}

	/*for (Renderable * renderable : myRenderables)
	{
		
		renderable->Submit(myRenderer);
	}*/


	myRenderer->End();
	myRenderer->Flush();

	myShader->unbind();
}