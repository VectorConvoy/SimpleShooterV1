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

StartScreen* ScreenManager::GetStartScreen()
{
    return mStartScreen;
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
        if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->GetAnimationDone())
        {
            //Reset the game

            //Switch to play screen here and start game
            mCurrentScreen = SCREENS::play;
            //mStartScreen->ResetAnimation();
            mPlayScreen->StartNewGame();
            mPlayScreen->SetGameStarted(true);
        }
        else
        {
            mStartScreen->Update();
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
        mStartScreen->Render();
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

    mStartScreen = new StartScreen();
    mPlayScreen = new PlayScreen();
    mCurrentScreen = SCREENS::start;
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

