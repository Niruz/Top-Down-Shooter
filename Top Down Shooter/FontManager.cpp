#include "FontManager.h"
#include "Font.h"

FontManager* FontManager::Instance()
{
	static FontManager instance;
	return &instance;
}
void FontManager::onInitialize()
{
	//LoadTexture("Textures/floor.png", "floor");
	LoadFont("Fonts/SourceSansPro-Light.ttf", "DefaultFont32", 32);
	LoadFont("Fonts/SourceSansPro-Light.ttf", "DefaultFont64", 64);

}
void FontManager::onDeinitialize()
{
	for (auto iterator : myFonts)
		delete iterator.second;
}
bool FontManager::LoadFont(std::string filename, std::string identifier, int size)
{
	myFonts[identifier] = new Font(identifier, filename, size);
	return true;
}
Font* FontManager::GetFont(std::string name)
{
	return myFonts[name];
}