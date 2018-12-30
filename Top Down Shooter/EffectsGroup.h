#pragma once

#include "Renderable.h"

class Effect;
class EffectsGroup : public Renderable
{
public:
	EffectsGroup(const glm::mat4& mat);
	EffectsGroup(const glm::mat4& mat, float zValue);
	virtual ~EffectsGroup();
	void Submit(RendererBase* renderer);

	void Add(Effect* renderable);

	void SetTransformationMatrix(const glm::mat4& mat) { myTransformationMatrix = mat; }
	glm::mat4 GetTransformationMatrix() const { return myTransformationMatrix; }

	void UpdateXYAxis(const glm::vec2& axis);
private:
	std::vector<Effect*> myRenderables;
	glm::mat4 myTransformationMatrix;

	float myZValue;

	//bad name, but this will increase the z value a bit for every added effect
	float myIncreaseZValue;
};