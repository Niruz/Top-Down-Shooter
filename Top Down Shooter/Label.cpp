#include "Label.h"
#include "Font.h"
#include "FontManager.h"
Label::Label(const std::string& text, float x, float y, Font* font, const glm::vec4& color)
	: Renderable(), myText(text), myFont(font)
{
	//myFont = font;
	myPosition = glm::vec3(x, y, 0);
	//myColor = color;
	SetColor(color);
}
Label::Label(const std::string& text, const glm::vec3& pos, Font* font, const glm::vec4& color)
	: Renderable(), myText(text), myFont(font)
{
	myFont = font;
	myPosition = pos;
	//myColor = color;
	SetColor(color);
}
Label::Label(const std::string& text, const glm::vec3& pos, const std::string& font, const glm::vec4& color)
	: Renderable(), myText(text)
{
	myFont = FontMan->GetFont(font);
	myPosition = pos;
	//myColor = color;
	SetColor(color);
}
void Label::Submit(RendererBase* renderer) const
{
	renderer->DrawString(myText, myPosition, *myFont,myColor);
}