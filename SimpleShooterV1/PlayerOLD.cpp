#include "PlayerOLD.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "MathHelper.h"

PlayerOLD::PlayerOLD()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = true;
	mAnimating = false;
	animationDone = true;
	mWasHit = false;
	currentDirection = UP;
	newDirection = UP;

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

PlayerOLD::PlayerOLD(std::string filename)
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	animationTimer = 0.0f;

	mVisible = true;
	mAnimating = false;
	animationDone = true;
	mWasHit = false;
	currentDirection = UP;
	newDirection = UP;
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

	SetAnimationSpeed(0.1f);

	AddCollider(new BoxCollider(mShip->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);


}

PlayerOLD::~PlayerOLD()
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

void PlayerOLD::Visible(bool visible)
{
	mVisible = visible;
}

void PlayerOLD::Hit(PhysicEntity* other)
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

bool PlayerOLD::WasHit()
{

	return mWasHit;
}

void PlayerOLD::LoadSpriteSheet(std::string filename)
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

bool PlayerOLD::IsAnimating()
{
	return mAnimating;
}

Texture* PlayerOLD::GetTexture()
{
	return mShip;
}

void PlayerOLD::SetAnimationSpeed(float speed)
{
	animationSpeed = speed;
}

void PlayerOLD::SetDirection(float nextDirection)
{
	newDirection = nextDirection;
	
	isAnimatingMovement = true;

	goalIndex = newDirection * FRAMES_PER_ANIMATION;

	if(newDirection == UP && (currentDirection == LEFT || currentDirection == UPLEFT || currentDirection == DOWNLEFT))
	{
		indexDelta = (int)ANIMATIONDIRECTION::forward;
	}
	else if (newDirection == LEFT && (currentDirection == UP || currentDirection == UPRIGHT) || currentDirection == UPLEFT)
	{
		indexDelta = (int)ANIMATIONDIRECTION::forward;
	}
	else if (currentDirection > newDirection)
	{
		indexDelta = (int)ANIMATIONDIRECTION::backward;
	}
	else
	{
		indexDelta = (int)ANIMATIONDIRECTION::forward;
	}

	setSpeedValues();
	SetBulletDirection(newDirection);
}

void PlayerOLD::SetBulletDirection(float nextDirection)
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

void PlayerOLD::RespawnPlayer()
{
	if (!GetActive())
	{
		SetActive(true);

		SetPosition(Vector2(Graphics::SCREEN_WIDTH/2, Graphics::SCREEN_HEIGHT/2));

		mVisible = true;
	}
}

void PlayerOLD::HandleMovementAnimation()
{
	//printf("INDEX DELTA: %f\n", (float) indexDelta);
	int delta = ((int)(animationTimer / timePerFrame)) * indexDelta;
	//printf("*******************************************************************************************\nDELTA: %f\nCURRENT INDEX: %f\n*************************************************************", (float)delta, (float) currentIndex);
	//TODO - Fix issue where going from up to left results in the animation going clockwise instead of counter clockwise
	int newIndex = currentIndex + delta;

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

void PlayerOLD::Update()
{
	
	if (mAnimating)
	{
		//Death animation still running 

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

				//Check if sprite is correct
				if (currentIndex != goalIndex)
				{
					mShip->SetClipped(rectCoordinates.at(goalIndex).first, rectCoordinates.at(goalIndex).second, frameWidth, frameHeight);
					currentIndex = goalIndex;
				}
				HandleMovement();
			}
			else
			{
				animationTimer += mTimer->DeltaTime();

				if (animationTimer >= animationSpeed)
				{
					isAnimatingMovement = false;
					animationTimer = animationSpeed - timePerFrame;
				}
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

void PlayerOLD::Render()
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

void PlayerOLD::initializeBullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
		mBullets[i]->RegisterPlayerBullets();
	}
}

void PlayerOLD::setSpeedValues()
{
	//mFrameCount = FRAMES_PER_ANIMATION;
	mFrameCount = fabsf(goalIndex - currentIndex);
	timePerFrame = animationSpeed / mFrameCount;
	animationTimer = 0.0f;
}

void PlayerOLD::HandleMovement()
{

	if (mInput->KeyDown(SDL_SCANCODE_W))
	{
		if (mInput->KeyDown(SDL_SCANCODE_A))
		{
			Translate(VEC2_UPLEFT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else if (mInput->KeyDown(SDL_SCANCODE_D))
		{
			Translate(VEC2_UPRIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else
		{
			Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
	}
	else if (mInput->KeyDown(SDL_SCANCODE_D))
	{
		if (mInput->KeyDown(SDL_SCANCODE_W))
		{
			Translate(VEC2_UPRIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else if (mInput->KeyDown(SDL_SCANCODE_S))
		{
			Translate(VEC2_DOWNRIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else
		{
			Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
	}
	else if (mInput->KeyDown(SDL_SCANCODE_S))
	{
		if (mInput->KeyDown(SDL_SCANCODE_A))
		{
			Translate(VEC2_DOWNLEFT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else if (mInput->KeyDown(SDL_SCANCODE_D))
		{
			Translate(VEC2_DOWNRIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else
		{		
			Translate(VEC2_DOWN* mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
	}
	else if (mInput->KeyDown(SDL_SCANCODE_A))
	{
		if (mInput->KeyDown(SDL_SCANCODE_W))
		{
			Translate(VEC2_UPLEFT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else if (mInput->KeyDown(SDL_SCANCODE_S))
		{
			Translate(VEC2_DOWNLEFT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
		else
		{
			Translate(VEC2_LEFT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		}
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

void PlayerOLD::HandleFiring()
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
