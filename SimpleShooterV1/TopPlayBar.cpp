#include "TopPlayBar.h"

TopPlayBar::TopPlayBar()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	//mTopBar = new GameEntity((Vector2(Graphics::Instance()->SCREEN_WIDTH * .5f, 20)));
	InitializeTopBar();

	mTotalShips = DEFAULT_LIVES;
}

TopPlayBar::~TopPlayBar()
{
	mTimer = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mOneUpText;
	mOneUpText = nullptr;

	delete mPlayerHealth;
	mPlayerHealth = nullptr;

	mPlayer = nullptr;
}

void TopPlayBar::Update()
{
	UpdateHealthBar();
}

void TopPlayBar::Render()
{
	mTopBar->Render();
	mBackground->Render();
	mOneUpText->Render();
	mPlayerHealth->Render();

	mShips->Render();

	for (int i = 0; i < DEFAULT_LIVES; i++)
	{
		if (mShipTextures[i]->GetActive())
		{
			mShipTextures[i]->Render();
		}
	}

}

void TopPlayBar::InitializeTopBar()
{
	SetTopBarEntities();
	InitializeLives();
	UpdateHealthBar();


	mShips = new GameEntity();
	mShips->SetParent(mTopBar);
}

void TopPlayBar::SetTopBarEntities()
{
	//Top bar enttities
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * .5f, 20.0f));
	mOneUpText = new Texture("1UP", "Boxy-Bold.ttf", 16, { 231, 255, 4 });
	mOneUpText->SetParent(mTopBar);
	mOneUpText->SetPosition(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.4f, 0.0f));

	//UpdateHealthBar();

	mBackground = new Texture(BACKGROUND_TOP_BAR);
	mBackground->SetPosition((Vector2(Graphics::Instance()->SCREEN_WIDTH * .5f, 20.0f)));
	mBackground->SetParent(mTopBar);

	mTopBar->SetParent(this);

}

void TopPlayBar::InitializeLives()
{
	mShips = new GameEntity();
	mShips->SetParent(mTopBar);

	for (int i = 0; i < DEFAULT_LIVES; i++)
	{
		mShipTextures[i] = new Texture(PLAYER_SHIP_NAME);
		mShipTextures[i]->SetParent(mShips);
		mShipTextures[i]->SetPosition(Vector2(FRAME_WIDTH * (i % DEFAULT_LIVES) + mOneUpText->GetPosition().x*1.5, 40.0f * (i / DEFAULT_LIVES) + mOneUpText->GetPosition().y));
		mShipTextures[i]->SetActive(true);
	}

	currentLives = DEFAULT_LIVES;
}

void TopPlayBar::UpdateHealthBar()
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

void TopPlayBar::SetPlayer(Player* player)
{
	mPlayer = player;
}

void TopPlayBar::SetLives(int lives)
{
	currentLives = lives;
}

int TopPlayBar::GetLives()
{
	return currentLives;
}

void TopPlayBar::LostALife()
{
	for (int i = mTotalShips - 1; i >= 0; i--)
	{
		if (mShipTextures[i]->GetActive())
		{
			mShipTextures[i]->SetActive(false);
			break;
		}
	}
}


/*
* Method to calculate which health bar file to use by calculating the correct
* value and then returning it in the correct format so we can append it
**/
std::string TopPlayBar::GetHealthFileNum()
{
	int healthNumber = 0;
	std::string healthFileName = "_0.png";
	
	if (mPlayer)
	{
		if (mPlayer->GetActive())
		{
			int playerHealth = mPlayer->GetHealth();

			playerHealthIncrements = (float) ceil(MAXIMUM_HEALTH / mPlayer->PLAYER_HEALTH);

			healthNumber = playerHealth * (int) playerHealthIncrements;

			healthFileName = "_" + std::to_string(healthNumber) + ".png";
		}
	}
	
	return healthFileName;
}
