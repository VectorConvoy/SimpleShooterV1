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

	SetTopBarEntities();

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
	else if (mInputManager->KeyPressed(SDL_SCANCODE_C))
	{
		SpawnEnemy((int)AIEngine::BEHAVIOR::seek);
		//Respawn Enemy
	}
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

void PlayScreen::SetTopBarEntities()
{
	//Top bar enttities
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * .5f, 80.0f));
	mPlayerLives = new Texture("1UP", "Boxy-Bold.ttf", 16, { 231, 255, 4 });
	mPlayerLives->SetParent(mTopBar);
	mPlayerLives->SetPosition(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));

	UpdateHealthBar();

	mTopBar->SetParent(this);
}


/*
* Method to calculate which health bar file to use by calculating the correct
* value and then returning it in the correct format so we can append it
**/
std::string PlayScreen::GetHealthFileNum()
{
	int healthNumber = 10;
	std::string healthFileName = "_10.png";
	
	if (mPlayer)
	{
		if (mPlayer->GetActive())
		{
			int playerHealth = mPlayer->GetHealth();

			playerHealthIncrements = ceil(MAXIMUM_HEALTH / mPlayer->PLAYER_HEALTH);

			healthNumber = playerHealth * playerHealthIncrements;

			healthFileName = "_" + std::to_string(healthNumber) + ".png";
		}
	}
	
	return healthFileName;
}

void PlayScreen::UpdateHealthBar()
{
	if (mPlayerHealth)
	{
		delete mPlayerHealth;
		mPlayerHealth = NULL;
	}

	mPlayerHealth = new Texture(HealthBar + GetHealthFileNum());
	mPlayerHealth->SetParent(mTopBar);
	mPlayerHealth->SetPosition(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));

	mPlayerHealth->SetScale(Vector2(0.5, 0.5));
}

void PlayScreen::SpawnEnemy(int behavior)
{
	std::shared_ptr<Enemy> temp = std::shared_ptr<Enemy>(new Enemy());
	temp->SetRotation(180);
	temp->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 4));
	temp->SetDebugBehavior(behavior);
	temp->SetActive(true);

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
		UpdateHealthBar();
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
}

void PlayScreen::Render()
{
	mBackground->Render();
	mPlayerLives->Render();
	mPlayerHealth->Render();

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
