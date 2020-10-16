#pragma once
#define _SCREENMANAGER_H

//#include "StartScreen.h"
#include "InputManager.h"
#include "PlayScreen.h"
#include "StartScreen.h"

class ScreenManager
{
public:
	static ScreenManager* Instance();
	static void Release();

	StartScreen* GetStartScreen();
	PlayScreen* GetPlayScreen();

	void Update();
	void Render();

private:

	enum class SCREENS {start, play};

	static ScreenManager* sInstance;
	
	InputManager* mInputManager;

	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

	SCREENS mCurrentScreen;

	ScreenManager();
	~ScreenManager();

};