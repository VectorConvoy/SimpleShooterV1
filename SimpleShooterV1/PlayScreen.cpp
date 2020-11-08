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

	topBar = new TopPlayBar();

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

	delete topBar;
	topBar = nullptr;

	delete mPlayer;
	mPlayer = NULL;

	delete mBackground;
	mBackground = NULL;

	for (std::shared_ptr<Enemy> enemy : mEnemies)
	{
		enemy = NULL;
	}

	mEnemies.clear();
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
	
	topBar->SetPlayer(mPlayer);
	//Spawn enemies

	mAIManager->SetPlayer(mPlayer);

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
	//else if (mInputManager->KeyPressed(SDL_SCANCODE_C))
	//{
	//	SpawnEnemy((int)AIEngine::BEHAVIOR::seek);
	//	//Respawn Enemy
	//}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_F))
	{
		SpawnEnemy((int)AIEngine::BEHAVIOR::flee);
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE))
	{
 		mPlayer->FireBullet();
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

void PlayScreen::SpawnEnemy(int behavior)
{
	std::shared_ptr<Enemy> temp = std::shared_ptr<Enemy>(new Enemy());
	temp->SetRotation(180);
	temp->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 4));
	//temp->SetDebugBehavior(behavior);
	temp->SetActive(true);

	temp->CreateBehaviorTree();

	mAIManager->AddEnemy(temp);
	mEnemies.push_back(temp);
}

void PlayScreen::CheckEnemyStatus()
{
	for (std::shared_ptr<Enemy> enemy : mEnemies)
	{

		if (!(*enemy).GetActive() && !(*enemy).GetAnimating())
		{
			mAIManager->RemoveEnemy(enemy);
			enemy.reset();

			mEnemies.erase(std::find(mEnemies.begin(), mEnemies.end()-1, enemy));
		}
	}

}

void PlayScreen::Update()
{
	if (mActive)
	{
		if (mPlayer)
		{
			mPlayer->CustomUpdate();
		}

		mPhysicsManager->Update();
		mAIManager->Update();
		CheckEnemyStatus();

		for (std::shared_ptr<Enemy> enemy : mEnemies)
		{
			if (enemy)
			{
				enemy->CustomUpdate();
			}
		}
	}

	topBar->Update();
}

void PlayScreen::Render()
{
	mBackground->Render();


	if (mActive)
	{
		if (mPlayer)
		{
			mPlayer->CustomRender();
		}
	}

	for (std::shared_ptr<Enemy> enemy : mEnemies)
	{
		enemy->CustomRender();	
	}

	topBar->Render();

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
