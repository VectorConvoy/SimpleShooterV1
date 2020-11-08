#include "Player.h"
#include "Ship.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Player::Player()
{
	sTimerInstance = Timer::Instance();
	mInputManager = InputManager::Instance();

	mVisible = true;
	mAnimating = false;
	mWasHit = false;
	isPlayer = true;
	currentDirection = UP;
	destinationDirection = UP;
	spriteAngle = 0;
	futureRotations = 0;
	currentRotations = 0;

	mMoveSpeed = (float) DEFAULT_SPEED;
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);

	mDeathAnimation = new AnimatedTexture(DEATH_ANIMATION, 0, 0, 64, 64, 4, 1.0f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this); //Unsure if it will work
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	LoadTextureFromFile(SHIP_NAME, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);

	PhysicEntity::AddCollider(new BoxCollider(shipTexture->ScaledDimensions()));
	InitializeBullets();

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	mActive = true;

}

Player::~Player()
{
}

void Player::InitializeBullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
		mBullets[i]->SetActive(false);
		mBullets[i]->RegisterPlayerBullets();
	}
}

void Player::SetBulletDirection(float nextDirection)
{
	Vector2 vec;

	if (nextDirection == UP)
	{
		vec = VEC2_UP;
	}
	else if (nextDirection == UPRIGHT)
	{
		vec = VEC2_UPRIGHT;
	}
	else if (nextDirection == RIGHT)
	{
		vec = VEC2_RIGHT;
	}
	else if (nextDirection == DOWNRIGHT)
	{
		vec = VEC2_DOWNRIGHT;
	}
	else if (nextDirection == DOWN)
	{
		vec = VEC2_DOWN;
	}
	else if (nextDirection == DOWNLEFT)
	{
		vec = VEC2_DOWNLEFT;
	}
	else if (nextDirection == LEFT)
	{
		vec = VEC2_LEFT;
	}
	else if (nextDirection == UPLEFT)
	{
		vec = VEC2_UPLEFT;
	}


	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!mBullets[i]->GetActive())
		{
			mBullets[i]->SetBulletDirection(vec);
		}
		mBullets[i]->SetShipDirection(vec);
	}
}

void Player::FireBullet()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!mBullets[i]->GetActive())
		{
			mBullets[i]->Fire(GetPosition());
			//Play audio here
			sAudioManagerInstance->PlaySFX("Laser-Shot-1.mp3");
			break;

		}
	}
	
}

void Player::CustomUpdate()
{
	//Update base ship class here
	//Add any additional updates here
	this->Update();

	if (mWasHit && mActive)
	{
		invincible = true;
	}

	if (invincible)
	{
		mInvincibleTimer += sTimerInstance->DeltaTime();
		InvinicibilityFlash();
		if (mInvincibleTimer >= INVINCIBILITY_TIME)
		{
			mInvincibleTimer = 0.0f;
			invincible = false;
			mWasHit = false;
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (mBullets[i]->GetActive())
		{
			mBullets[i]->Update();
		}
	}
}

void Player::CustomRender()
{
	if (mVisible)
	{
		this->Render();
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}
	PhysicEntity::Render();

}

void Player::RespawnPlayer()
{
	if (mActive)
	{
		this->Respawn(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
	}
}

void Player::CheckKeyInput()
{
	if (mInputManager->KeyDown(SDL_SCANCODE_W))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_A))
		{
			Move(VEC2_UPLEFT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D))
		{
			Move(VEC2_UPRIGHT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else
		{
			Move(VEC2_UP * mMoveSpeed * sTimerInstance->DeltaTime());
		}
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_D))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_W))
		{
			Move(VEC2_UPRIGHT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S))
		{
			Move(VEC2_DOWNRIGHT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else
		{
			Move(VEC2_RIGHT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_S))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_A))
		{
			Move(VEC2_DOWNLEFT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D))
		{
			Move(VEC2_DOWNRIGHT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else
		{
			Move(VEC2_DOWN * mMoveSpeed * sTimerInstance->DeltaTime());
		}
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_A))
	{
		if (mInputManager->KeyDown(SDL_SCANCODE_W))
		{
			Move(VEC2_UPLEFT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S))
		{
			Move(VEC2_DOWNLEFT * mMoveSpeed * sTimerInstance->DeltaTime());
		}
		else
		{
			Move(VEC2_LEFT* mMoveSpeed * sTimerInstance->DeltaTime());
		}
	}
	else if (mInputManager->KeyDown(SDL_SCANCODE_SPACE))
	{
		//Fire 
	}
	else
	{
		Move(VEC2_ZERO);
	}

}

void Player::SetPlayerDirection(float direct)
{
	destinationDirection = direct;

	if (direct != STOP)
	{
		SetBulletDirection(direct);
	}

	Vector2 tempVector;

	if (direct == UP)
	{
		tempVector = VEC2_UP * mMoveSpeed * sTimerInstance->DeltaTime();
		//Move(VEC2_UP * mMoveSpeed * sTimerInstance->DeltaTime());
	}
	else if (direct == UPRIGHT)
	{
		tempVector = VEC2_UPRIGHT * mMoveSpeed * sTimerInstance->DeltaTime();

	}
	else if (direct == RIGHT)
	{
		tempVector = VEC2_RIGHT * mMoveSpeed * sTimerInstance->DeltaTime();

	}
	else if (direct == DOWNRIGHT)
	{
		tempVector = VEC2_DOWNRIGHT * mMoveSpeed * sTimerInstance->DeltaTime();

	}
	else if (direct == DOWN)
	{
		tempVector = VEC2_DOWN * mMoveSpeed * sTimerInstance->DeltaTime();

	}
	else if (direct == DOWNLEFT)
	{
		tempVector = VEC2_DOWNLEFT * mMoveSpeed * sTimerInstance->DeltaTime();

	}
	else if (direct == LEFT)
	{
		tempVector = VEC2_LEFT * mMoveSpeed * sTimerInstance->DeltaTime();

	}
	else if (direct == UPLEFT)
	{
		tempVector = VEC2_UPLEFT * mMoveSpeed * sTimerInstance->DeltaTime();
	}
	else if (direct == STOP)
	{
		tempVector = VEC2_ZERO;
	}

	SetDestVector(tempVector);

}

void Player::InvinicibilityFlash()
{
	if (fmod(mInvincibleTimer, 0.5)> 0.25f)
	{
		mVisible = false;
	}
	else
	{
		mVisible = true;
	}
}

