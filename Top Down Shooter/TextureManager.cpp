#include "TextureManager.h"
#include <iostream>

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

	LoadTexture("Textures/floor.png", "floor",false,false,false);
	LoadTexture("Textures/floor2.png", "floor2", false, false, false);
	LoadTexture("Textures/wall.png", "wall", false, false, false);
	LoadTexture("Textures/cursor.jpg", "cursor", false, false, false);;
	LoadTexture("Textures/cursor2.jpg", "cursor2", false, false, false);
	LoadTexture("Textures/wall.jpg", "player", false, false, false);
	LoadTexture("Textures/512Atlas.png", "atlas", false, false, false);
	LoadTexture("Textures/background.png", "moonbackground", false, true, false);
	LoadTexture("Textures/graveyard2.png", "graveyard", true, true, false);
	LoadTexture("Textures/mountains2.png", "mountains", true, true, false);
	LoadTexture("Textures/spritesheet.png", "hero", true, false, false);
	LoadTexture("Textures/skeletonnormalsprites.png", "skeleton", true, false, false);
	LoadTexture("Textures/ghostspritesheet.png", "ghost", true, false, false);
	LoadTexture("Textures/gatospritesheet.png", "gato", true, false, false);
	LoadTexture("Textures/eyemonstersheet.png", "eyemonster", true, false, false);
	LoadTexture("Textures/demon.png", "demon", true, false, false);
	LoadTexture("Textures/demon-idle.png", "demonidle", true, false, false); 
	LoadTexture("Textures/demon2.png", "demon2", true, false, false);
	LoadTexture("Textures/demon-idle3.png", "demonidle3", true, false, false);
	LoadTexture("Textures/plasma2.png", "plasma", true, false, false);
	LoadTexture("Textures/testtile.png", "grass", true, false, false);
	LoadTexture("Textures/testtile2.png", "grass2", true, false, false);
	LoadTexture("Textures/testtile_1.png", "grass_1", true, false, false);
	LoadTexture("Textures/testtile2_1.png", "grass2_1", true, false, false);
	LoadTexture("Textures/tilepillar1.png", "pillar1", true, false, false);
	LoadTexture("Textures/tilepillar2.png", "pillar2", true, false, false);
	LoadTexture("Textures/spikes.png", "spikes", true, false, false);

	LoadTexture("Textures/bush-large.png", "bushlarge", true, false, false);
	LoadTexture("Textures/bush-small.png", "bushsmall", true, false, false);
	LoadTexture("Textures/statue.png", "statue", true, false, false);
	LoadTexture("Textures/stone-1.png", "stone1", true, false, false);
	LoadTexture("Textures/stone-2.png", "stone2", true, false, false);
	LoadTexture("Textures/stone-3.png", "stone3", true, false, false);
	LoadTexture("Textures/stone-4.png", "stone4", true, false, false);
	LoadTexture("Textures/tree-1.png", "tree1", true, false, false);
	LoadTexture("Textures/tree-2.png", "tree2", true, false, false);
	LoadTexture("Textures/tree-3.png", "tree3", true, false, false);
	LoadTexture("Textures/floatinggrass.png", "floatinggrass", true, false, false);
	LoadTexture("Textures/floatingsolid.png", "floatingsolid", true, false, false);
	LoadTexture("Textures/floatingsolid2.png", "floatingsolid2", true, false, false);
	LoadTexture("Textures/floatingtileright.png", "floatingright", true, false, false);
	LoadTexture("Textures/floatingtilerightgrass.png", "floatingrightgrass", true, false, false);
	LoadTexture("Textures/floatingtileleftgrass.png", "floatingleftgrass", true, false, false);
	LoadTexture("Textures/floatingtileleft.png", "floatingleft", true, false, false);
	LoadTexture("Textures/stairtile.png", "stair", true, false, false);
	LoadTexture("Textures/healthtemp.png", "hpbar", true, false, false);
	LoadTexture("Textures/spikedpillar.png", "spikedpillar", true, false, false);
	LoadTexture("Textures/firegolemsheet8.png", "firegolem", true, false, false);
	LoadTexture("Textures/ghoulspritesheet.png", "ghoul", true, false, false);
	LoadTexture("Textures/undeadwarriorsheet6.png", "undeadwarrior", true, false, false); //2 then 5
	LoadTexture("Textures/reapersheet2.png", "reaper", true, false, false);
	LoadTexture("Textures/impsheet.png", "imp", true, false, false);
	LoadTexture("Textures/necromancersheet5.png", "necromancer", true, false, false);
	LoadTexture("Textures/necromancerprojectilesheet.png", "necromancerProjectile", true, false, false);
	LoadTexture("Textures/impprojectilesheet.png", "impProjectile", true, false, false);
	LoadTexture("Textures/enemydeathsheet.png", "enemyDeath", true, false, false);
	LoadTexture("Textures/adventurersheet21_4.png", "adventurer2", true, false, false);
	LoadTexture("Textures/adventurerprojectilesheet.png", "adventurerProjectile", true, false, false);
	LoadTexture("Textures/adventurerprojectilesheet2.png", "arrowProjectile", true, false, false);
	LoadTexture("Textures/hiteffect2.png", "hiteffect", true, false, false);
	LoadTexture("Textures/hitspritesheet.png", "hiteffectslow", true, false, false);
	LoadTexture("Textures/bubblessheet2.png", "bubbles", true, false, false);
	LoadTexture("Textures/midnightsheet2.png", "midnight", true, false, false);
	LoadTexture("Textures/spellspritesheet.png", "spell", true, false, false);
	LoadTexture("Textures/slide1.png", "slide1", true, false, false);
	LoadTexture("Textures/slide2.png", "slide2", true, false, false);
	LoadTexture("Textures/spritehp.png", "hppotion", true, false, false);
	LoadTexture("Textures/pickupdestroyed.png", "pickupdestroyed", true, false, false);
	LoadTexture("Textures/coinsheet.png", "coins", true, false, false);
	LoadTexture("Textures/bloodsheet3.png", "bloodeffect", true, false, false);
	LoadTexture("Textures/bloodsheet3.png", "bloodeffect2", true, false, false);
	LoadTexture("Textures/enemydiesheet2.png", "deatheffect", true, false, false);
	LoadTexture("Textures/enemyhiteffectsheet.png", "enemyhiteffect", true, false, false);
	LoadTexture("Textures/spriteswordhitsheet.png", "swordhiteffect", true, false, false);
	LoadTexture("Textures/floatingsolidspiked.png", "floatingsolidspiked", true, false, false);
	LoadTexture("Textures/slideeffectsprite.png", "slideeffect", true, false, false);
	LoadTexture("Textures/adventurerdropkickeffect.png", "dropkickeffect", true, false, false);
	LoadTexture("Textures/backgrounddungeon.png", "dungeonbackground", true, false, false);
	LoadTexture("Textures/pillarbackground.png", "pillarbackground", true, false, false);
	LoadTexture("Textures/dungeontile1.png", "dungeontile1", true, false, false);
	LoadTexture("Textures/dungeonfloor1.png", "dungeonfloor1", true, false, false);
	LoadTexture("Textures/dungeonfloor2.png", "dungeonfloor2", true, false, false);
	LoadTexture("Textures/dungeonfloor3.png", "dungeonfloor3", true, false, false);
	LoadTexture("Textures/dungeonfloor4.png", "dungeonfloor4", true, false, false);
	LoadTexture("Textures/dungeonroof1.png", "dungeonroof1", true, false, false);
	LoadTexture("Textures/dungeonroof2.png", "dungeonroof2", true, false, false);
	LoadTexture("Textures/dungeonroof3.png", "dungeonroof3", true, false, false);
	LoadTexture("Textures/dungeonroof4.png", "dungeonroof4", true, false, false);
	LoadTexture("Textures/dungeongrass1.png", "dungeongrass1", true, false, false);
	LoadTexture("Textures/dungeongrass2.png", "dungeongrass2", true, false, false);
	LoadTexture("Textures/dungeongrass3.png", "dungeongrass3", true, false, false);
	LoadTexture("Textures/dungeonedgeleft.png", "dungeonedgeleft", true, false, false);
	LoadTexture("Textures/dungeonedgeright.png", "dungeonedgeright", true, false, false);
	LoadTexture("Textures/dungeonbigtile.png", "dungeonbigtile", true, false, false);

	LoadTexture("Textures/Cage_1.png", "dungeoncage1", true, false, false);
	LoadTexture("Textures/Cage_2.png", "dungeoncage2", true, false, false);
	LoadTexture("Textures/Cage_3.png", "dungeoncage3", true, false, false);

	LoadTexture("Textures/Coffin_1.png", "dungeoncoffin1", true, false, false);
	LoadTexture("Textures/Coffin_2.png", "dungeoncoffin2", true, false, false);
	LoadTexture("Textures/Coffin_3.png", "dungeoncoffin3", true, false, false);
	//LoadTexture("Textures/hitspritesheet.png", "hiteffect", true, false, false);
	/*LoadTexture("Textures/1.png", "1");
	LoadTexture("Textures/2.png", "2");.png
	LoadTexture("Textures/3.png", "3");...png
	LoadTexture("Textures/4.png", "4");
	LoadTexture("Textures/5.png", "5");
	LoadTexture("Textures/6.png", "6");*/

	for(int i=0 ; i < 36; i++)
	{
		LoadTexture("Textures/"+std::to_string(i)+".png", std::to_string(i), false, false, false);
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
bool TextureManager::LoadTexture(std::string filename, std::string identifier, GLboolean alpha, GLboolean isBackground, GLboolean repeating)
{
	if (GetTexture(filename) != nullptr)
	{
		std::cout << "Texture: " + filename + " already loaded.\n";
		return false;
	}
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
		mTextures[identifier]->setImageFormat(GL_BGRA);
		mTextures[identifier]->setInternalFormat(GL_BGRA);
	//	mTextures[identifier]->setImageFormat(GL_RGBA);
	//	mTextures[identifier]->setInternalFormat(GL_RGBA);
	}
	if (isBackground)
	{
		mTextures[identifier]->setFilterFormat(GL_LINEAR,GL_LINEAR);
		//mTextures[identifier]->setWrapperFormat(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
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
void TextureManager::GetUVCoordinates(int row, int column, std::vector<glm::vec2>& vec)
{
	//Maybe pass this in as a reference
/*	vec.push_back(glm::vec2(0, 0));
	vec.push_back(glm::vec2(0, 1));
	vec.push_back(glm::vec2(1, 1));
	vec.push_back(glm::vec2(1, 0));
	*/
	float x1 = (row * 32.0f) / 512.0f;
	float x2 = ((row + 1) * 32.0f) / 512.0f;
	float y1 = (column * 32.0f) / 512.0f;
	float y2 = ((column + 1) * 32.0f) /512.0f;
	
	vec.push_back(glm::vec2(x1, y1));
	vec.push_back(glm::vec2(x1, y2));
	vec.push_back(glm::vec2(x2, y2));
	vec.push_back(glm::vec2(x2, y1));
	int shit = 5;
	
	
	//0 
	//X = 32.0f/512, 64.0/512
	//Y = 
}