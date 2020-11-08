#pragma once
#define _TOPPLAYBAR_H


#include "timer.h"
#include "AudioManager.h"
#include "AnimatedTexture.h"
#include "Player.h"

class TopPlayBar : public GameEntity
{
public:
	const std::string PLAYER_SHIP_NAME = "PlayerLife.png";
	const std::string HealthBar = "HealthBars/VIDA";
	const std::string BACKGROUND_TOP_BAR = "TopPlayBarBackground.png";
	const int MAXIMUM_HEALTH = 10;
	static const int DEFAULT_LIVES = 3;

	const int FRAME_HEIGHT = 32;
	const int FRAME_WIDTH = 32;

	TopPlayBar();
	~TopPlayBar();

	void Update();
	void Render();

	void InitializeTopBar();
	void SetTopBarEntities();
	void InitializeLives();
	void UpdateHealthBar();
	void SetPlayer(Player* player);

	void SetLives(int lives = DEFAULT_LIVES);
	
	std::string GetHealthFileNum();

private:

	float playerHealthIncrements;

	Timer* mTimer;
	AudioManager* mAudio;

	GameEntity* mTopBar;
	Texture* mBackground;
	Texture* mOneUpText;
	Texture* mPlayerHealth;

	Player* mPlayer;

	//Keep track of lives and their textures
	GameEntity* mShips;
	Texture* mShipTextures[DEFAULT_LIVES];
	int mTotalShips;

};