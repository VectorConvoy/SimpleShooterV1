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


    if (!Graphics::Initialized())
    {
        mQuit = true;
    }


    mInputManager = InputManager::Instance();
    mTimer = Timer::Instance();

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

    delete mTexture;
    mTexture = NULL;
}

void GameManager::EarlyUpdate()
{
    mInputManager->Update();
}

void GameManager::Update()
{
    checkKeyPress();
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
        printf("Pressed D Key\n");

        mPlayScreen->GetPlayer()->SetDirection(Player::DIRECTION::right);
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_W))
    {
        printf("Pressed W Key\n");

        mPlayScreen->GetPlayer()->SetDirection(Player::DIRECTION::up);
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_A))
    {
        printf("Pressed A Key\n");
        mPlayScreen->GetPlayer()->SetDirection(Player::DIRECTION::left);
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_S))
    {
        printf("Pressed S Key\n");
        mPlayScreen->GetPlayer()->SetDirection(Player::DIRECTION::down);
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_X))
    {
        printf("Pressed X key\n");
        mPlayScreen->GetPlayer()->RespawnPlayer();
        //Respawn Player;
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_C))
    {
        printf("Pressed C Key\n");

        mPlayScreen->GetEnemy()->RespawnEnemy();
        //Respawn Enemy
    }
}

void GameManager::checkKeyRelease()
{
    //if (mInputManager->KeyReleased(SDL_SCANCODE_D))
    //{
    //    //mAudioManager->PlaySFX("8bit_hit_13.wav", 0, 0);
    //    shipSprites->SetShipMoving(false, ShipAnimation::DIRECTION::right);
    //    printf("Released D Key\n");
    //}
    //else if (mInputManager->KeyReleased(SDL_SCANCODE_W))
    //{
    //    //mAudioManager->PlaySFX("8bit_hit_13.wav", 0, 0);
    //    shipSprites->SetShipMoving(false, ShipAnimation::DIRECTION::up);
    //    printf("Released W Key\n");

    //}
    //else if (mInputManager->KeyReleased(SDL_SCANCODE_A))
    //{
    //    shipSprites->SetShipMoving(false, ShipAnimation::DIRECTION::left);
    //    printf("Released A Key\n");

    //}
    //else if (mInputManager->KeyReleased(SDL_SCANCODE_S))
    //{
    //    shipSprites->SetShipMoving(false, ShipAnimation::DIRECTION::down);
    //   printf("Released S Key\n");
    //}
}

void GameManager::HandleCollision()
{
    if (!mPlayerHit)
    {
        if (mPlayer->WasHit())
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
