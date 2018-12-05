#include "Group.h"
#include <glm/gtc/matrix_transform.hpp>
Group::Group(const glm::mat4& mat)
	: myTransformationMatrix(mat)
{

}
Group::Group(const glm::mat4& mat, float zValue)
	: myTransformationMatrix(mat), myZValue(zValue)
{

}
Group::~Group()
{
	for (Renderable* renderable : myRenderables)
		delete renderable;
}
void Group::Submit(RendererBase* renderer) const 
{
	renderer->Push(myTransformationMatrix);
	for(Renderable* renderable : myRenderables)
	{
		if (!renderable->myMarkedForDeletion)
			renderable->Submit(renderer);
	}
	renderer->Pop();
};
void Group::Add(Renderable* renderable)
{
	myRenderables.push_back(renderable);
}

void Group::UpdateXYAxis(const glm::vec2& axis)
{ 
	glm::mat4 trans = glm::mat4(1.0f);
	myTransformationMatrix = glm::translate(trans,(glm::vec3(axis.x, axis.y, myZValue)));
}