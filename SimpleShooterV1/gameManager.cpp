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
    mQuit = false;
    mGraphics = Graphics::Instance();

    if (!Graphics::Initialized())
    {
        mQuit = true;
    }

    mAssetManager = AssetManager::Instance();

    mInputManager = InputManager::Instance();

    mAudioManager = AudioManager::Instance();

    mTimer = Timer::Instance();

    //shipSprites = new ShipAnimation("SpriteSheet.png", 0.1f);

    //nTexture = shipSprites->GetCurrentTexture();
    //nTexture->SetPosition(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
    //shipSprites->UpdatePositionForAllTextures(nTexture->GetPosition());

    //mTexture = new AnimatedTexture("SpriteSheet.png", 0, 0, 64, 64, 12, 2.0f, AnimatedTexture::vertical);
    
    //nTexture->SetPosition(Vector2(400,200));

    mPlayer = new Player("SpriteSheet.png");

    mPlayer->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
    mPlayer->SetAnimationSpeed(0.1f);

}

GameManager::~GameManager()
{
    AssetManager::Release();
    mAssetManager = NULL;  
    
    Graphics::Release();
    mGraphics = NULL;

    InputManager::Release();
    mInputManager = NULL;

    AudioManager::Release();
    mAudioManager = NULL;

    Timer::Release();
    mTimer = NULL;

    delete mTexture;
    mTexture = NULL;

    delete mPlayScreen;
    mPlayScreen = NULL;

    delete mPlayer;
    mPlayer = NULL;
}

void GameManager::EarlyUpdate()
{
    mInputManager->Update();
}

void GameManager::Update()
{
    checkKeyPress();
    //if (shipSprites->GetShipMoving() && shipSprites->GetAnimationDone())
    //{
    //    nTexture->SetPosition(shipSprites->newPosition());
    //}
    //shipSprites->Update();
    //nTexture = shipSprites->GetCurrentTexture();
    //nTexture->Update();
    //mTexture->Rotate(10 * mTimer->DeltaTime());

    mPlayer->Update();
}

void GameManager::LateUpdate()
{
    mInputManager->UpdatePreviousInput();
    mTimer->Reset();

}

void GameManager::checkKeyPress()
{
    if (mInputManager->KeyPressed(SDL_SCANCODE_D))
    {
        //mAudioManager->PlaySFX("8bit_hit_13.wav", 0, 0);
        //shipSprites->SetShipMoving(true, ShipAnimation::DIRECTION::right);
        //shipSprites->SetAnimationDone(false);
        //shipSprites->SetDeltaPosition(1, 0);
        printf("Pressed D Key\n");

        mPlayer->SetDirection(Player::DIRECTION::right);
    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_W))
    {
        //mAudioManager->PlaySFX("8bit_hit_13.wav", 0, 0);
        //shipSprites->SetShipMoving(true, ShipAnimation::DIRECTION::up);
        //shipSprites->SetAnimationDone(false);
        //shipSprites->SetDeltaPosition(0, -1);
        printf("Pressed W Key\n");

        mPlayer->SetDirection(Player::DIRECTION::up);


    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_A))
    {
        //shipSprites->SetShipMoving(true, ShipAnimation::DIRECTION::left);
        //shipSprites->SetAnimationDone(false);
        //shipSprites->SetDeltaPosition(-1, 0);
        printf("Pressed A Key\n");


        mPlayer->SetDirection(Player::DIRECTION::left);


    }
    else if (mInputManager->KeyPressed(SDL_SCANCODE_S))
    {
        //shipSprites->SetShipMoving(true, ShipAnimation::DIRECTION::down);
        //shipSprites->SetAnimationDone(false);
        //shipSprites->SetDeltaPosition(0, 1);
        printf("Pressed S Key\n");


        mPlayer->SetDirection(Player::DIRECTION::down);

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



void GameManager::Render()
{
    mGraphics->ClearBackBuffer();

    //Draw calls here
    //nTexture->Render();
    mPlayer->Render();
    mGraphics->Render();

}
