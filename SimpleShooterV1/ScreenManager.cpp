#include "ScreenManager.h"


ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new ScreenManager();
    }
    return sInstance;
}

void ScreenManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

PlayScreen* ScreenManager::GetPlayScreen()
{
    return mPlayScreen;
}

void ScreenManager::Update()
{
    switch (mCurrentScreen)
    {
    case SCREENS::start:
        //mStartScreen->render();
        if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
        {
            //Reset the game

            //Switch to play screen here and start game
            mCurrentScreen = SCREENS::play;
            //mStartScreen->ResetAnimation();
            mPlayScreen->StartNewGame();
        }
        break;

    case SCREENS::play:
        
        mPlayScreen->Update();
        if (mInputManager->KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            //return to start screen or exit game
        }
        else if (mInputManager->KeyPressed(SDL_SCANCODE_DELETE))
        {
            //Reset game
            mPlayScreen->StartNewGame();
            mPlayScreen->SetGameStarted(true);

        }
        break;

    }
}

void ScreenManager::Render()
{
    switch (mCurrentScreen)
    {
    case SCREENS::start:
        break;

    case SCREENS::play:
        mPlayScreen->Render();
        break;
    }
}

ScreenManager::ScreenManager()
{
    //mStartScreen = new StartScreen();

    mInputManager = InputManager::Instance();

    mPlayScreen = new PlayScreen();
    mCurrentScreen = SCREENS::play;
}

ScreenManager::~ScreenManager()
{
    //Delete screens here

    //No need to release as we do that in the GameManager
    mInputManager = NULL;

    //delete mStartScreen
    //mStartScreen = NULL;

    delete mPlayScreen;
    mPlayScreen = NULL;

}

