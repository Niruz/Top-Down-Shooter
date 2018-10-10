#pragma once

#include "Renderable.h"


class RendererBase
{
protected:
	virtual void Submit(const Renderable* renderable) = 0;
	virtual void Flush() = 0;
};