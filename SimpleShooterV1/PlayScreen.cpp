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

	mRoundStartDelay = 3.0f;
	mRoundStarted = false;
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInputManager = NULL;
	mAudioManager = NULL;
	mPhysicsManager = NULL;
	mAIManager = NULL;

	delete mBackground;
	mBackground = NULL;

	delete topBar;
	topBar = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mPlayer;
	mPlayer = NULL;


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
	mGameStarted = false;

	mAudioManager->PlayMusic("Start_Sounds_003.wav", 0);

	InitializePlayer();
	topBar->SetPlayer(mPlayer);
	
	//Add player to AIManager
	mAIManager->SetPlayer(mPlayer);

	currentRound = 1;

	SetupStartLabel();

}

void PlayScreen::StartNextRound()
{
	currentRound++;
	mRoundStartTimer = 0.0f;
	mRoundStarted = false;

	DestroyStartLabel();
	SetupStartLabel();

}

void PlayScreen::InitializePlayer()
{
	delete mPlayer;
	if (mPlayer)
	{
		delete mPlayer;
	}

	mPlayer = new Player();
	mPlayer->SetShipFileName(PlayerShipName);
	mPlayer->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.75));
	mPlayer->SetActive(true);
}

void PlayScreen::SetGameStarted(bool started)
{
	mActive = started;
}

bool PlayScreen::GetGameStarted()
{
	return mActive;
}

void PlayScreen::SetRoundStarted(bool started)
{
	mRoundStarted = started;
}

bool PlayScreen::GetRoundStarted()
{
	return mRoundStarted;
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
	else if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE))
	{
		mPlayer->FireBullet();
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN))
	{
		//Only capture the input and start round if it is the beginning
		if (!mRoundStarted && currentRound < 2)
		{
			mRoundStarted = true;
			SpawnEnemy((int)AIEngine::BEHAVIOR::flee);

			mAudioManager->PlayMusic("bgm.wav");
			//Begin round animation
		}
		else if (!mPlayer->GetActive() && topBar->GetLives() > 0)
		{
			ResetPlayer();
		}

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

void PlayScreen::PlayerDeath()
{
	topBar->SetLives(topBar->GetLives() - 1);

	if (topBar->GetLives() <= 0)
	{
		//Game Over logic here
	}
	else
	{
		topBar->LostALife();
	}

	mAudioManager->PauseMusic();
}

void PlayScreen::ResetPlayer()
{
	mPlayer->SetActive(true);
	mPlayer->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.75));
	mPlayer->SetHealth(Ship::PLAYER_HEALTH);

	mAudioManager->ResumeMusic();
}

void PlayScreen::Update()
{
	if (mActive)
	{
		if (mGameStarted && mRoundStarted)
		{
			topBar->Update();
		}

		//Level delay
		if (!mRoundStarted)
		{
			mRoundStartTimer += mTimer->DeltaTime();

			if (mRoundStartTimer >= mRoundStartDelay)
			{
				mRoundStarted = true;
				SpawnEnemy((int)AIEngine::BEHAVIOR::flee);
			}
		}
		else
		{
			if (mGameStarted && mRoundStarted)
			{
				topBar->Update();
			}

			if (mGameStarted)
			{
				//Level delay
				if (!mRoundStarted)
				{
					mRoundStartTimer += mTimer->DeltaTime();

					if (mRoundStartTimer >= mRoundStartDelay)
					{
						mRoundStarted = true;
					}
				}
				else
				{
					if (mPlayer)
					{
						mPlayer->CustomUpdate();
					}

					mPhysicsManager->Update();
					mAIManager->Update();

					for (std::shared_ptr<Enemy> enemy : mEnemies)
					{
						enemy->CustomUpdate();	
					}
				}
			}
			else
			{
				if (mRoundStarted && !mRoundAnimation)
				{
					mGameStarted = true;
					mAudioManager->PlaySFX("whoosh1.wav");
				}
			}
			}
	}

	
}

void PlayScreen::Render()
{	
	mBackground->Render();
	topBar->Render();


	if (mActive)
	{
		if (!mGameStarted || !mRoundStarted)
		{
			mStartLabel->Render();
		}
		else
		{
			//Round started, render game assets 
			if (mPlayer)
			{
				mPlayer->CustomRender();
			}

			for (std::shared_ptr<Enemy> enemy : mEnemies)
			{
				enemy->CustomRender();
			}

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

void PlayScreen::SetupStartLabel()
{

	std::ostringstream oss;
	oss << "ROUND " << currentRound;
	mStartLabel = new Texture(oss.str(), "alagard_by_pix3m-d6awiwp.ttf", 32, { 255, 0, 0 });
	mStartLabel->SetParent(this);
	mStartLabel->SetPosition(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.45f));
}

void PlayScreen::DestroyStartLabel()
{
	if (mStartLabel)
	{
		delete mStartLabel;
		mStartLabel = nullptr;
	}
}
