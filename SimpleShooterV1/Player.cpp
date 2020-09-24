#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = true;
	mAnimating = false;
	animationDone = true;
	mWasHit = false;
	currentDirection = DIRECTION::up;
	newDirection = DIRECTION::up;

	mMoveSpeed = 200.0f;
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);

	mDeathAnimation = new AnimatedTexture(DeathAnimation, 0, 0, 64, 64, 4, 1.0f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this);
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	initializeBullets();

	LoadSpriteSheet(ShipName);

	AddCollider(new BoxCollider(mShip->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::Player(std::string filename)
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	animationTimer = 0.0f;

	mVisible = true;
	mAnimating = false;
	animationDone = true;
	mWasHit = false;
	currentDirection = DIRECTION::up;
	newDirection = DIRECTION::up;
	currentIndex = 0;
	goalIndex = 0;

	mMoveSpeed = 200.0f;
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);

	mDeathAnimation = new AnimatedTexture(DeathAnimation, 0, 0, 64, 64, 4, 0.5f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this);
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	initializeBullets();

	LoadSpriteSheet(filename);

	AddCollider(new BoxCollider(mShip->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);


}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;

	delete mShip;
	mShip = nullptr;

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = NULL;
	}

}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

void Player::Hit(PhysicEntity* other)
{	

	//Death animation and handling here
	mWasHit = true;
	
	if (!mAnimating && GetActive())
	{
		SetActive(false);
		mDeathAnimation->ResetAnimation();
		mAnimating = true;
		
	}

	//Play Death Audio

}

bool Player::WasHit()
{

	return mWasHit;
}

void Player::LoadSpriteSheet(std::string filename)
{
	Texture* temp = new Texture(filename);

	frameWidth = temp->GetTextureWidth() / FRAMES_PER_ROW;
	frameHeight = temp->GetTextureHeight() / FRAMES_PER_COL;

	mShip = new Texture(filename, 0, 0, frameWidth, frameHeight);

	delete temp;
	temp = NULL;


	for (int y = 0; y < FRAMES_PER_COL; y++)
	{
		for (int x = 0; x < FRAMES_PER_ROW; x++)
		{
			rectCoordinates.push_back(std::make_pair(frameWidth * x, frameHeight * y));

		}
	}

	mShip->SetParent(this);

}

bool Player::IsAnimating()
{
	return mAnimating;
}

Texture* Player::GetTexture()
{
	return mShip;
}

void Player::SetAnimationSpeed(float speed)
{
	animationSpeed = speed;
}

void Player::SetDirection(DIRECTION direction)
{
	newDirection = direction;

	isAnimatingMovement = true;

	if (newDirection == DIRECTION::up && currentDirection == DIRECTION::left)
	{
		indexDelta = (int) ANIMATIONDIRECTION::forward;
	}
	else if (newDirection == DIRECTION::left && currentDirection == DIRECTION::up)
	{
		indexDelta = (int)ANIMATIONDIRECTION::backward;
	}
	else if (currentDirection > newDirection)
	{
		indexDelta = (int)ANIMATIONDIRECTION::backward;
	}
	else if (currentDirection == newDirection)
	{
		indexDelta = 0;
		isAnimatingMovement = false;
	}
	else
	{
		indexDelta = (int)ANIMATIONDIRECTION::forward;
	}

	goalIndex = (int)newDirection * FRAMES_PER_ANIMATION;

	setSpeedValues();
	SetBulletDirection(newDirection);
}

void Player::SetBulletDirection(DIRECTION direction)
{
	Vector2 vec;
	switch (direction)
	{
	case DIRECTION::up:
		vec = VEC2_UP;
		break;
	case DIRECTION::right:
		vec = VEC2_RIGHT;
		break;
	case DIRECTION::down:
		vec = VEC2_DOWN;
		break;
	case DIRECTION::left:
		vec = VEC2_LEFT;
		break;
	default:
		vec = VEC2_ONE;
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

void Player::RespawnPlayer()
{
	if (!GetActive())
	{
		SetActive(true);

		SetPosition(Vector2(Graphics::SCREEN_WIDTH/2, Graphics::SCREEN_HEIGHT/2));

		mVisible = true;
	}
}

void Player::HandleMovementAnimation()
{
	int newIndex = currentIndex + indexDelta;

	if (newIndex < 0)
	{
		newIndex += (int)rectCoordinates.size();
	}
	else if (newIndex >= rectCoordinates.size())
	{
		newIndex %= rectCoordinates.size();
	}
	
	mShip->SetClipped(rectCoordinates.at(newIndex).first, rectCoordinates.at(newIndex).second, frameWidth, frameHeight);

	currentIndex = newIndex;

	if (currentIndex == goalIndex)
	{
		isAnimatingMovement = false;
	}
}

void Player::Update()
{
	if (mAnimating)
	{
		if (mWasHit)
		{
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else
	{
		if (GetActive())
		{
			if (!isAnimatingMovement)
			{
				currentDirection = newDirection;
				HandleMovement();
			}
			else
			{
				HandleMovementAnimation();
			}

			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}
}

void Player::Render()
{
	if (mVisible)
	{
		if (mAnimating)
		{
			mDeathAnimation->Render();
		}
		else
		{
			if (GetActive())
			{
				mShip->Render();
			}
			else
			{
				//If the ship is not active, do not render it and set it's visibility to be false
				mVisible = false;
			}
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}
	PhysicEntity::Render();
}

void Player::initializeBullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
		mBullets[i]->RegisterPlayerBullets();
	}
}

void Player::setSpeedValues()
{
	//mFrameCount = FRAMES_PER_ANIMATION;
	mFrameCount = goalIndex - currentIndex;
	timePerFrame = animationSpeed / mFrameCount;
	animationTimer = 0.0f;
}

void Player::HandleMovement()
{

	if (mInput->KeyDown(SDL_SCANCODE_W))
	{
		Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_D))
	{
		Translate(VEC2_RIGHT* mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_S))
	{
		Translate(VEC2_DOWN* mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A))
	{
		Translate(VEC2_LEFT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
	}

	Vector2 position = GetPosition(GameEntity::SPACE::local);

	if (position.x + mShip->GetTextureWidth() / 2 > mMoveBounds.x)
	{
		position.x = mMoveBounds.x - mShip->GetTextureWidth() / 2;
	}
	else if (position.x - mShip->GetTextureWidth() / 2.0f < 0)
	{
		position.x = mShip->GetTextureWidth() / 2.0f;
	}

	if (position.y + mShip->GetTextureHeight() / 2.0f > mMoveBounds.y)
	{
		position.y = mMoveBounds.y - mShip->GetTextureHeight() / 2;
	}
	else if (position.y - mShip->GetTextureHeight() / 2.0f < 0)
	{
		position.y = mShip->GetTextureHeight() / 2.0f;
	}

	SetPosition(position);
	mShip->UpdatePosition((int) position.x, (int) position.y);

}

void Player::HandleFiring()
{
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->GetActive())
			{
				mBullets[i]->Fire(GetPosition());

				//Play audio here

				break;

			}
		}
	}
}
