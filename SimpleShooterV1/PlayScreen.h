#pragma once
#define _PLAYSCREEN_H

#include "InputManager.h"
#include "timer.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "AIEngine.h"
#include <memory>

class PlayScreen : public GameEntity
{
public:

	const std::string PlayerShipName = "SpriteSheet.png";
	const std::string EnemyShipName = "enemyship1.png";
	const std::string DeathAnimation = "ship_explosion.png";
	const std::string HealthBar = "HealthBars/VIDA";
	const int MAXIMUM_HEALTH = 10;

	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void SetGameStarted(bool started);
	bool GetGameStarted();

	Player* GetPlayer();
	//Enemy* GetEnemy();

	void checkKeyPress();
	void checkKeyRelease();

	void SetTopBarEntities();
	std::string GetHealthFileNum();
	void UpdateHealthBar();

	void SpawnEnemy(int behavior = AIEngine::BEHAVIOR::flee);

	void CheckEnemyStatus();
		
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

	Texture* mBackground;

	//Top Bar Entities
	GameEntity* mTopBar;
	Texture* mPlayerLives;
	Texture* mPlayerHealth;

	Player* mPlayer;
	//Enemy* mEnemy; //Enemy for debugging purposes

	std::vector<std::shared_ptr<Enemy>> mEnemies;

	bool mPlayerHit;

	void StartLevel();

	void SetupPhysics();
	
};