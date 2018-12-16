#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::Instance()
{
	static SoundManager instance;
	return &instance;
}
void SoundManager::OnInitialize()
{
	SoundEngine = createIrrKlangDevice();
}
void SoundManager::OnDeinitialize()
{
	delete SoundEngine;
}