#include "gameManager.h"

GameManager* GameManager::singleInstance = NULL;

GameManager* GameManager::Instance()
{
    if (singleInstance == NULL)
    {
        singleInstance = new GameManager();
    }
    return singleInstance;
}

void GameManager::Release()
{
    delete singleInstance;
    singleInstance = NULL;
}

void GameManager::Run()
{
    while (!mQuit)
    {
        mTimer->Update();
        while (SDL_PollEvent(&mEvents) != 0)
        {
            if (mEvents.type == SDL_QUIT)
            {
                mQuit = true;
            }
        }
        if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE)
        {
            EarlyUpdate();
            Update();
            LateUpdate();
            Render();


        }

    }
}

GameManager::GameManager()
{
    //mPlayerHit = false;
    mQuit = false;
    mGraphics = Graphics::Instance();
    mScreenManager = ScreenManager::Instance();
    mStartScreen = mScreenManager->GetStartScreen();
    mPlayScreen = mScreenManager->GetPlayScreen();

    if (!Graphics::Initialized())
    {
        mQuit = true;
    }

    mInputManager = InputManager::Instance();
    mTimer = Timer::Instance();

    mAssetManager = AssetManager::Instance();
    mAudioManager = AudioManager::Instance();


    mPlayerHit = false;

    //mAIManager = AIEngine::Instance();
}

GameManager::~GameManager()
{
    ScreenManager::Release();
    mScreenManager = NULL;

    AssetManager::Release();
    mAssetManager = NULL;  
    
    Graphics::Release();
    mGraphics = NULL;

    InputManager::Release();
    mInputManager = NULL;

    AudioManager::Release();
    mAudioManager = NULL;

    PhysicsManager::Release();
    mPhysicsManager = nullptr;

    Timer::Release();
    mTimer = NULL;

    delete mStartScreen;
    mStartScreen = NULL;

    delete mTexture;
    mTexture = NULL;
}

void GameManager::EarlyUpdate()
{
    mInputManager->Update();
}

void GameManager::Update()
{
    if (mPlayScreen)
    {
        if (mPlayScreen->GetGameStarted())
        {
            mPlayScreen->checkKeyPress();
            mPlayScreen->checkKeyRelease();
        }

    }


    mScreenManager->Update();
}

void GameManager::LateUpdate()
{
    mInputManager->UpdatePreviousInput();
    mTimer->Reset();

}

void GameManager::checkKeyPress()
{
    
    mPlayScreen = mScreenManager->GetPlayScreen();

    if (mInputManager->KeyPressed(SDL_SCANCODE_D))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_S))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(DOWNRIGHT);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_W))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(UPRIGHT);
        }
        else
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(RIGHT);
        }

    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_W))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_A))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(UPLEFT);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_D))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(UPRIGHT);
        }
        else
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(UP);
        }
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_A))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_W))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(UPLEFT);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_S))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(DOWNLEFT);
        }
        else
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(LEFT);
        }

    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_S))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_D))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(DOWNRIGHT);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_A))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(DOWNLEFT);
        }
        else
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(DOWN);
        }
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_X))
    {
        if (mPlayScreen->GetActive())
        {
            mPlayScreen->GetPlayer()->RespawnPlayer();
            //Respawn Player;
        }
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_C))
    {
        if (mPlayScreen->GetActive())
        {
            //mPlayScreen->GetEnemy()->RespawnEnemy();
            //Respawn Enemy
        }
    }
    else
    {
        mPlayScreen->GetPlayer()->SetPlayerDirection(STOP);
    }
}

void GameManager::checkKeyRelease()
{
    if (mInputManager->KeyReleased(SDL_SCANCODE_D))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_S))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(DOWN);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_W))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(UP);
        }
    }
    else if (mInputManager->KeyReleased(SDL_SCANCODE_W))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_A))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(LEFT);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_D))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(RIGHT);
        }
    }
    else if (mInputManager->KeyReleased(SDL_SCANCODE_A))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_W))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(UP);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_S))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(DOWN);
        }
    }
    else if (mInputManager->KeyReleased(SDL_SCANCODE_S))
    {
        if (mInputManager->KeyDown(SDL_SCANCODE_D))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(RIGHT);
        }
        else if (mInputManager->KeyDown(SDL_SCANCODE_A))
        {
            mPlayScreen->GetPlayer()->SetPlayerDirection(LEFT);
        }
    }
}

void GameManager::HandleCollision()
{
    if (!mPlayerHit)
    {
        if (mPlayer->GetHit())
        {
            mPlayerHit = true;
        }
    }
}


void GameManager::Render()
{
    mGraphics->ClearBackBuffer();

    //Draw calls here
    //nTexture->Render();
    
    mScreenManager->Render();
    mGraphics->Render();

}
