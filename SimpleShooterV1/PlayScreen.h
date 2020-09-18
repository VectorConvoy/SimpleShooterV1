#pragma once
#define _PLAYSCREEN_H

#include "InputManager.h"
#include "GameEntity.h"
#include "timer.h"
#include "Player.h"

class PlayScreen : public GameEntity
{
public:
	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();

private:
	Timer* mTimer;
	InputManager* mInputManager;

	Player* mPlayer;

	
};