#pragma once

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

//Singleton

#include "AudioManager.h"
#include "PlayScreen.h"
#include "PhysicsManager.h"
#include "ScreenManager.h"
#include "AIEngine.h"

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
	bool mPlayerHit;

	Graphics* mGraphics;
	Timer* mTimer;
	AnimatedTexture* mTexture;
	Texture* nTexture;

	ScreenManager* mScreenManager;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

	Player* mPlayer;
	Enemy* mEnemy;

	AssetManager* mAssetManager;
	InputManager* mInputManager;
	AudioManager* mAudioManager;
	PhysicsManager* mPhysicsManager;
	//AIEngine* mAIManager;

	//ShipAnimation* shipSprites;

	SDL_Event mEvents;

	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void checkKeyPress();
	void checkKeyRelease();

	void HandleCollision();

	void Render();
};


#endif