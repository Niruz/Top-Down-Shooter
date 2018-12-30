#include "EffectsGroup.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Effect.h"
#include "Group.h"
#include "AnimatedSprite.h"
EffectsGroup::EffectsGroup(const glm::mat4& mat)
	: myTransformationMatrix(mat), myIncreaseZValue(0.0f)
{

}
EffectsGroup::EffectsGroup(const glm::mat4& mat, float zValue)
	: myTransformationMatrix(mat), myZValue(zValue), myIncreaseZValue(0.0f)
{

}
EffectsGroup::~EffectsGroup()
{
	for (Effect* renderable : myRenderables)
		delete renderable;
	myRenderables.clear();
}
void EffectsGroup::Submit(RendererBase* renderer)
{
	renderer->Push(myTransformationMatrix);
	//Add this to some sort of dynamic group if we want all renderables to be deleted when marked for deletion
	std::vector<Effect*>::iterator it = myRenderables.begin();

	while (it != myRenderables.end())
	{

	if ((*it)->GetMarkedForDeletion())
	{

		it = myRenderables.erase(it);
	}
	else
	{
		(*it)->mySprite->Submit(renderer);
		++it;
	}

	}
	/*for (Effect* renderable : myRenderables)
	{
		if (!renderable->GetMarkedForDeletion())
			renderable->mySprite->Submit(renderer);
	}*/
	renderer->Pop();
};
void EffectsGroup::Add(Effect* renderable)
{
	renderable->myAnimatedSprite->myPosition.z = myIncreaseZValue;
	myIncreaseZValue += 0.00001;
	myRenderables.push_back(renderable);
}

void EffectsGroup::UpdateXYAxis(const glm::vec2& axis)
{
	glm::mat4 trans = glm::mat4(1.0f);
	myTransformationMatrix = glm::translate(trans, (glm::vec3(axis.x, axis.y, myZValue)));
}