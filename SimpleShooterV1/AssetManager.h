#pragma once
#define _ASSETMANAGER_H

#include "graphics.h"
#include <SDL_mixer.h>
#include <map>

class AssetManager {

public:
	static AssetManager* Instance();
	static void Release();
	SDL_Texture* GetTexture(std::string filename);
	SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color);
	
	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);


private:
	static AssetManager* sInstance;

	//Use maps to store loaded textures so we do not need to load them twice
	std::map<std::string, SDL_Texture*> mTextures;
	std::map<std::string, SDL_Texture*> mTexturesOfText;
	std::map<std::string, TTF_Font*> mFonts;
	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*> mSFX;

	AssetManager();
	~AssetManager();
	TTF_Font* GetFont(std::string filename, int size);


};