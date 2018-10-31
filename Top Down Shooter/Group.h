#pragma once

#include "Renderable.h"

class Group : public Renderable
{
public:
	Group(const glm::mat4& mat);
	~Group();
	void Submit(RendererBase* renderer) const override;

	void Add(Renderable* renderable);

	void SetTransformationMatrix(const glm::mat4& mat) { myTransformationMatrix = mat; }
private:
	std::vector<Renderable*> myRenderables;
	glm::mat4 myTransformationMatrix;
};