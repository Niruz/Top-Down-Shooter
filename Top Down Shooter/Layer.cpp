#include "Layer.h"

Layer::Layer()
{

}
Layer::Layer(RendererBase* renderer, Shader* shader, const glm::mat4& projectionMatrix)
	:myRenderer(renderer), myShader(shader), myProjectionMatrix(projectionMatrix)
{
	myShader->bind();
	myShader->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, myProjectionMatrix);
	myShader->unbind();
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
	for (Renderable * renderable : myRenderables)
		myRenderer->Submit(renderable);
	myRenderer->End();
	myRenderer->Flush();

	myShader->unbind();
}