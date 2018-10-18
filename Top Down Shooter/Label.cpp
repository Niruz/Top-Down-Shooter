#include "Label.h"

Label::Label(const std::string& text, float x, float y, const glm::vec4& color)
	: Renderable(), myText(text)
{
	myPosition = glm::vec3(x, y, 0);
	myColor = color;
}
Label::Label(const std::string& text, const glm::vec3& pos, const glm::vec4& color)
	: Renderable(), myText(text)
{
	myPosition = pos;
	myColor = color;
}
void Label::Submit(RendererBase* renderer) const
{
	renderer->DrawString(myText, myPosition, myColor);
}