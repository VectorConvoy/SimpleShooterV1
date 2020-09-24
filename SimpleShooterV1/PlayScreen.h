#pragma once
#define _PLAYSCREEN_H

#include "InputManager.h"
#include "timer.h"
#include "Player.h"
#include "Enemy.h"
#include "AudioManager.h"
#include "PhysicsManager.h"

class PlayScreen : public GameEntity
{
public:

	const std::string PlayerShipName = "SpriteSheet.png";
	const std::string EnemyShipName = "enemyship1.png";
	const std::string DeathAnimation = "ship_explosion.png";

	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void SetGameStarted(bool started);
	bool GetGameStarted();

	Player* GetPlayer();
	Enemy* GetEnemy();
		
	void Update();
	void Render();

private:

	bool mGameStarted;
	//bool mLevelStarted;
	//int mCurrentStage;

	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;
	PhysicsManager* mPhysicsManager;

	Texture* mBackground;

	Player* mPlayer;
	Enemy* mEnemy; //Enemy for debugging purposes

	bool mPlayerHit;

	void StartLevel();

	void SetupPhysics();
	
};