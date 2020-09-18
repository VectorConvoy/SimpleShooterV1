#pragma once

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

//Singleton

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ShipAnimation.h"
#include "PlayScreen.h"

class GameManager 
{
public:
	static GameManager* Instance();
	static void Release();

	void Run();

private:
	static GameManager* singleInstance;
	
	const int FRAME_RATE = 60;

	bool mQuit;
	Graphics* mGraphics;
	Timer* mTimer;
	AnimatedTexture* mTexture;
	Texture* nTexture;
	PlayScreen* mPlayScreen;
	Player* mPlayer;

	AssetManager* mAssetManager;

	InputManager* mInputManager;

	AudioManager* mAudioManager;

	ShipAnimation* shipSprites;

	SDL_Event mEvents;

	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void checkKeyPress();
	void checkKeyRelease();

	void Render();
};


#endif