#pragma once
#define _STARTSCREEN_H

#include "AnimatedTexture.h"
#include "InputManager.h"

class StartScreen : public GameEntity
{
public:

	StartScreen();
	~StartScreen();

	bool GetAnimationDone();

	void ResetAnimation();

	void Update();
	void Render();


private:
	
	Timer* mTimer;

	//Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mEnter;

	//Title Entity
	GameEntity* mTitle;
	Texture* mTitle1;
	Texture* mTitle2;

	//Bottom Bar Entities
	GameEntity* mBottomBar;
	Texture* GVSUCopyRight;

	//Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

};