#include "Group.h"

Group::Group(const glm::mat4& mat)
	: myTransformationMatrix(mat)
{

}
void Group::Submit(RendererBase* renderer) const 
{
	renderer->Push(myTransformationMatrix);
	for(Renderable* renderable : myRenderables)
	{
		renderable->Submit(renderer);
	}
	renderer->Pop();
};
void Group::Add(Renderable* renderable)
{
	myRenderables.push_back(renderable);
}