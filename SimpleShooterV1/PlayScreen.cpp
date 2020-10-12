#include "PlayScreen.h"
#include "AIEngine.h"


PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();
	mPhysicsManager = PhysicsManager::Instance();
	mAIManager = AIEngine::Instance();

	SetupPhysics();

	mBackground = new Texture("space_custom.png");
	mBackground->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	//mPlayer = new Player();
	//mPlayer->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInputManager = NULL;
	mAudioManager = NULL;
	mPhysicsManager = NULL;
	mAIManager = NULL;

	if (mPlayer)
	{
		delete mPlayer;
	}
	mPlayer = NULL;

	if (mEnemy)
	{
		delete mEnemy;
	}
	mEnemy = NULL;

	delete mBackground;
	mBackground = NULL;
}

void PlayScreen::StartNewGame()
{
	mActive = false;
	mPlayerHit = false;

	delete mPlayer;
	if (mPlayer)
	{
		delete mPlayer;
	}

	mPlayer = new Player();
	mPlayer->SetShipFileName(PlayerShipName);
	mPlayer->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
	mPlayer->SetActive(true);
	//Spawn enemies

	if (mEnemy)
	{
		delete mEnemy;
	}
	
	mEnemy = new Enemy();
	mEnemy->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 4));
	mEnemy->SetRotation(180);

	mAIManager->SetPlayer(mPlayer);
	mAIManager->AddEnemy(mEnemy);
	mAIManager->ActivateAI();

}

void PlayScreen::SetGameStarted(bool started)
{
	mActive = started;
}

bool PlayScreen::GetGameStarted()
{
	return mActive;
}

Player* PlayScreen::GetPlayer()
{
	return mPlayer;
}

Enemy* PlayScreen::GetEnemy()
{
	return mEnemy;
}

void PlayScreen::checkKeyPress()
{
	if (mInputManager->KeyPressed(SDL_SCANCODE_D))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_S))
		{
			mPlayer->SetPlayerDirection(DOWNRIGHT);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_W))
		{
			mPlayer->SetPlayerDirection(UPRIGHT);
		}
		else
		{
			mPlayer->SetPlayerDirection(RIGHT);
		}

	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_W))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_A))
		{
			mPlayer->SetPlayerDirection(UPLEFT);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D))
		{
			mPlayer->SetPlayerDirection(UPRIGHT);
		}
		else
		{
			mPlayer->SetPlayerDirection(UP);
		}
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_A))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_W))
		{
			mPlayer->SetPlayerDirection(UPLEFT);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S))
		{
			mPlayer->SetPlayerDirection(DOWNLEFT);
		}
		else
		{
			mPlayer->SetPlayerDirection(LEFT);
		}
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_S))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_D))
		{
			mPlayer->SetPlayerDirection(DOWNRIGHT);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_A))
		{
			mPlayer->SetPlayerDirection(DOWNLEFT);
		}
		else
		{
			mPlayer->SetPlayerDirection(DOWN);
		}
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_X))
	{
		mPlayer->RespawnPlayer();
		//Respawn Player;
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_C))
	{
		mEnemy->RespawnEnemy();
		//Respawn Enemy
	}
}

void PlayScreen::checkKeyRelease()
{
	if (mInputManager->KeyReleased(SDL_SCANCODE_D))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_S))
		{
			mPlayer->SetPlayerDirection(DOWN);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_W))
		{
			mPlayer->SetPlayerDirection(UP);
		}
		else
		{
			mPlayer->SetPlayerDirection(STOP);
		}
	}
	else if (mInputManager->KeyReleased(SDL_SCANCODE_W))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_A))
		{
			mPlayer->SetPlayerDirection(LEFT);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D))
		{
			mPlayer->SetPlayerDirection(RIGHT);
		}
		else
		{
			mPlayer->SetPlayerDirection(STOP);
		}
	}
	else if (mInputManager->KeyReleased(SDL_SCANCODE_A))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_W))
		{
			mPlayer->SetPlayerDirection(UP);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S))
		{
			mPlayer->SetPlayerDirection(DOWN);
		}
		else
		{
			mPlayer->SetPlayerDirection(STOP);
		}
	}
	else if (mInputManager->KeyReleased(SDL_SCANCODE_S))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_D))
		{
			mPlayer->SetPlayerDirection(RIGHT);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_A))
		{
			mPlayer->SetPlayerDirection(LEFT);
		}
		else
		{
			mPlayer->SetPlayerDirection(STOP);
		}
	}
}

void PlayScreen::Update()
{
	if (mActive)
	{
		if (mPlayer)
		{
			mPlayer->Update();
		}

		if (mEnemy)
		{
			mEnemy->Update();
		}
		mPhysicsManager->Update();
		mAIManager->Update();

	}
	else
	{

	}
}

void PlayScreen::Render()
{
	//mPlayer->Render();
	mBackground->Render();
	if (mActive)
	{
		if (mPlayer)
		{
			mPlayer->Render();
		}

		if (mEnemy)
		{
			mEnemy->Render();
		}
	}

}

void PlayScreen::SetupPhysics()
{
	//Set collision layers for player and enemies
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Enemy | PhysicsManager::CollisionFlags::EnemyProjectiles);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Enemy, PhysicsManager::CollisionFlags::Friendly | PhysicsManager::CollisionFlags::FriendlyProjectile);

	//Set collision layers for player projectile and enemy projectiles
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectiles, PhysicsManager::CollisionFlags::Enemy);
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::EnemyProjectiles, PhysicsManager::CollisionFlags::Friendly);
}
