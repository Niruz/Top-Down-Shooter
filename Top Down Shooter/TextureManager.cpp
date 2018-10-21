#include "TextureManager.h"


TextureManager* TextureManager::Instance()
{
	static TextureManager instance;
	return &instance;
}
void TextureManager::onInitialize()
{
	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif

	LoadTexture("Textures/floor.png", "floor");
	LoadTexture("Textures/floor2.png", "floor2");
	LoadTexture("Textures/wall.png", "wall");
	LoadTexture("Textures/cursor.jpg", "cursor");
	LoadTexture("Textures/wall.jpg", "player");
	LoadTexture("Textures/512Atlas.png", "atlas");
	/*LoadTexture("Textures/1.png", "1");
	LoadTexture("Textures/2.png", "2");
	LoadTexture("Textures/3.png", "3");
	LoadTexture("Textures/4.png", "4");
	LoadTexture("Textures/5.png", "5");
	LoadTexture("Textures/6.png", "6");*/

	for(int i=0 ; i < 36; i++)
	{
		LoadTexture("Textures/"+std::to_string(i)+".png", std::to_string(i));
	}
}
void TextureManager::onDeinitialize()
{
	for (auto iterator : mTextures)
		delete iterator.second;

	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif
}
bool TextureManager::LoadTexture(std::string filename, std::string identifier, GLboolean alpha)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename.c_str());
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	mTextures[identifier] = new Texture();

	if (alpha)
	{
		mTextures[identifier]->setImageFormat(GL_RGBA);
		mTextures[identifier]->setInternalFormat(GL_RGBA);
	}

	mTextures[identifier]->Generate(width, height, bits);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);


	//return success
	return true;
}
Texture* TextureManager::GetTexture(std::string name)
{
	return mTextures[name];
}
