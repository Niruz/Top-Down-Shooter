#pragma once
#include "RendererBase.h"
#include <deque>

class StaticSprite;
class Renderer : public RendererBase
{
public:
	void Submit(const Renderable* renderable) override;
	void Flush() override;

private:
	std::deque<const StaticSprite*> myRenderQueue;
};