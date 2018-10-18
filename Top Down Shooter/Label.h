#pragma once
#include "Renderable.h"
#include <string>
class Label : public Renderable
{
public:
	Label(const std::string& text, float x, float y, const glm::vec4& color);
	Label(const std::string& text, const glm::vec3& pos, const glm::vec4& color);
	void Submit(RendererBase* renderer) const override;
public:

	std::string myText;
};