#pragma once

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

//Singleton

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ShipAnimation.h"
#include "PlayScreen.h"
#include "Enemy.h"
#include "PhysicsManager.h"
#include "ScreenManager.h"

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
	PlayScreen* mPlayScreen;

	Player* mPlayer;
	Enemy* mEnemy;

	AssetManager* mAssetManager;
	InputManager* mInputManager;
	AudioManager* mAudioManager;
	PhysicsManager* mPhysicsManager;

	ShipAnimation* shipSprites;

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