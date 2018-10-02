#pragma once

#include "Texture.h"
#include <map>


#define TextureMan TextureManager::Instance()

class TextureManager
{
public:
	static TextureManager* Instance();

	///Initialization
	void onInitialize();
	///Cleanup
	void onDeinitialize();

	//identifier is what we refer the texture as
	bool LoadTexture(std::string filename, std::string identifier, GLboolean alpha = false);

	Texture* GetTexture(std::string name);


private:
	TextureManager() {};
	TextureManager(const TextureManager&);
	TextureManager& operator = (const TextureManager&);
	~TextureManager() {};

	std::map<std::string, Texture*> mTextures;
};
