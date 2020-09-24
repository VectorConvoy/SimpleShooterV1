#include "PlayScreen.h"


PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();
	mPhysicsManager = PhysicsManager::Instance();

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
	mGameStarted = false;
	mPlayerHit = false;

	delete mPlayer;
	if (mPlayer)
	{
		delete mPlayer;
	}

	mPlayer = new Player(PlayerShipName);
	mPlayer->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	//Spawn enemies

	if (mEnemy)
	{
		delete mEnemy;
	}
	
	mEnemy = new Enemy(EnemyShipName);
	mEnemy->SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 4));
	//mEnemy->SetRotation(180);

	

}

void PlayScreen::SetGameStarted(bool started)
{
	mGameStarted = started;
}

bool PlayScreen::GetGameStarted()
{
	return mGameStarted;
}

Player* PlayScreen::GetPlayer()
{
	return mPlayer;
}

Enemy* PlayScreen::GetEnemy()
{
	return mEnemy;
}

void PlayScreen::Update()
{
	if (mGameStarted)
	{
		mPlayer->Update();
		mEnemy->Update();
		mPhysicsManager->Update();

	}
	else
	{

	}
}

void PlayScreen::Render()
{
	//mPlayer->Render();
	mBackground->Render();
	if (mGameStarted)
	{
		mPlayer->Render();
		mEnemy->Render();
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
