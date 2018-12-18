#pragma once
#include "Layer.h"

//This is used for the effects / enemies layer to remove any renderables we no longer need
class DynamicLayer : public Layer
{
public:
	DynamicLayer();
public:
	DynamicLayer(RendererBase* renderer, Shader* shader, const glm::mat4& projectionMatrix);
public:
	virtual ~DynamicLayer();
	virtual void Render();

};
