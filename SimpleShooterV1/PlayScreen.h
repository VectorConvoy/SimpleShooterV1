#pragma once
#define _PLAYSCREEN_H

#include "InputManager.h"
#include "timer.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "AIEngine.h"
#include <memory>
#include "TopPlayBar.h"

class PlayScreen : public GameEntity
{
public:

	const std::string PlayerShipName = "SpriteSheet.png";
	const std::string EnemyShipName = "enemyship1.png";
	const std::string DeathAnimation = "ship_explosion.png";
	
	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	void StartNextRound(); //Loads and sets up next round

	void InitializePlayer();

	void SetGameStarted(bool started);
	bool GetGameStarted();

	void SetRoundStarted(bool started);
	bool GetRoundStarted();

	void SetGameOver(bool over);
	bool GetGameOver();
	
	Player* GetPlayer();
	//Enemy* GetEnemy();

	void checkKeyPress();
	void checkKeyRelease();

	void SpawnEnemy(int behavior = AIEngine::BEHAVIOR::flee);

	void CheckEnemyStatus();

	void PlayerDeath();
	void ResetPlayer();
	void ResetEnemy();

	void Update();
	void Render();

private:

	bool mActive;
	//bool mLevelStarted;
	//int mCurrentStage;

	float playerHealthIncrements;

	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;
	PhysicsManager* mPhysicsManager;
	AIEngine* mAIManager;


	//Top Bar and entities
	TopPlayBar* topBar;
	Texture* mBackground;
	Player* mPlayer;
	
	//Start components
	Texture* mStartLabel;
	float mRoundStartTimer;
	float mRoundStartDelay;

	bool mGameStarted;
	bool mRoundStarted;
	bool mRoundAnimation;
	int currentRound;
	bool gameOver;

	std::vector<std::shared_ptr<Enemy>> mEnemies;

	bool mPlayerHit;

	void SetupPhysics();

	void SetupStartLabel();
	void DestroyStartLabel();
	
};