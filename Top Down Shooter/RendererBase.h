#pragma once

#include "Renderable.h"


class RendererBase
{
protected:
	std::vector<glm::mat4> myTransformationStack;
protected:
	RendererBase() 
	{
		myTransformationStack.push_back(glm::mat4(1.0f));
	}
public:
	void Push(const glm::mat4& mat, bool doOverride = false)
	{
		if (doOverride)
		{
			myTransformationStack.push_back(mat);
		}
		else
		{
			myTransformationStack.push_back(myTransformationStack.back() * mat);
		}
		
	}
	void Pop() 
	{
		if(myTransformationStack.size() > 1)
			myTransformationStack.pop_back();
	}
	virtual void Begin(){}
	virtual void End(){}
	virtual void Submit(const Renderable* renderable) = 0;
	virtual void Flush() = 0;
};