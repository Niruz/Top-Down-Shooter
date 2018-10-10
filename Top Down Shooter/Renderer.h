#pragma once
#include "RendererBase.h"

#include <deque>

class Renderer : public RendererBase
{
public:
	void Submit(const Renderable* renderable) override;
	void Flush() override;

private:
	std::deque<const Renderable*> myRenderQueue;
};