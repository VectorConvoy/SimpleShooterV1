#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mPlayer = new Player();
	mPlayer->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInputManager = NULL;

	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::Update()
{

}

void PlayScreen::Render()
{
	mPlayer->Render();
}
