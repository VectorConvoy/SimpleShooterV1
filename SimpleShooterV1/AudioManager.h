#pragma once
#define _AUDIOMANAGER_H
#include "AssetManager.h"

class AudioManager
{
public:
	static AudioManager* Instance();
	static void Release();

	void PlayMusic(std::string filename, int loops = -1); //Loop being -1 means loop forever
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(std::string filename, int loops = 0, int channel = 0); //SFX usually play once so 0 is a good default
private:

	static AudioManager* sInstance;

	AssetManager* mAssetManager;

	AudioManager();
	~AudioManager();
};