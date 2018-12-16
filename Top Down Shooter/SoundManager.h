#pragma once
#include <irrklang/irrKlang.h>
#define SoundMan SoundManager::Instance()
using namespace irrklang;
class SoundManager
{
public:
	static SoundManager* Instance();

	///Initialization
	void OnInitialize();
	///Cleanup
	void OnDeinitialize();

	ISoundEngine* GetSoundEngine() { return SoundEngine; }

	ISoundEngine *SoundEngine;

private:
	SoundManager() {};
	SoundManager(const SoundManager&);
	SoundManager& operator = (const SoundManager&);
	~SoundManager() {};

};
