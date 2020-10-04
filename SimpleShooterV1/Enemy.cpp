#include "Enemy.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Enemy::Enemy()
{
	mTimer = Timer::Instance();

	mVisible = true;
	mAnimating = false;
	animationDone = true;
	currentDirection = DIRECTION::up;
	newDirection = DIRECTION::up;

	mMoveSpeed = 50.0f;
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);

	mDeathAnimation = new AnimatedTexture(DeathAnimation, 0, 0, 64, 64, 4, 0.5f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this);
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	InitializeBullets();

	LoadSpriteSheet("enemy1.png");

	AddCollider(new BoxCollider(mShip->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Enemy);
}

Enemy::Enemy(std::string filename)
{
	mTimer = Timer::Instance();

	mVisible = true;
	mAnimating = false;
	animationDone = true;
	currentDirection = DIRECTION::down;
	newDirection = DIRECTION::down;

	//mMoveSpeed = 50.0f;
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
	mDeathAnimation = new AnimatedTexture(DeathAnimation, 0, 0, 64, 64, 4, 0.5f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this);
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	InitializeBullets();

	LoadSpriteSheet(filename);

	mShip->SetRotation((float)currentDirection);
	

	AddCollider(new BoxCollider(mShip->ScaledDimensions()));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Enemy);

}

Enemy::~Enemy()
{

}

void Enemy::Hit(PhysicEntity* other)
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

void Enemy::RespawnEnemy()
{
	if (!GetActive())
	{
		SetActive(true);

		SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 4));

		mVisible = true;
	}
}

void Enemy::Fire()
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

void Enemy::Move()
{
	switch (currentDirection)
	{
	case DIRECTION::up:
		Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		break;
	case DIRECTION::down:
		Translate(VEC2_DOWN * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		break;
	case DIRECTION::left:
		Translate(VEC2_LEFT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		break;
	case DIRECTION::right:
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::SPACE::world);
		break;
	default:
		break;

	}
}

bool Enemy::IsAnimating()
{
    return false;
}

bool Enemy::WasHit()
{
	return mWasHit;
}

Texture* Enemy::GetTexture()
{
	return mShip;
}

void Enemy::SetMovementSpeed(float speed)
{
	mMoveSpeed = speed;
}

void Enemy::SetDirection(DIRECTION direction)
{
	newDirection = direction;

	isAnimatingMovement = true;

	if (newDirection == DIRECTION::up && currentDirection == DIRECTION::left)
	{
		angleDelta = ROTATION_SPEED;
	}
	else if (newDirection == DIRECTION::left && currentDirection == DIRECTION::up)
	{
		angleDelta = ROTATION_SPEED * -1;
	}
	else if (currentDirection > newDirection)
	{
		angleDelta = ROTATION_SPEED * -1;
	}
	else if (currentDirection == newDirection)
	{
		angleDelta = 0;
		isAnimatingMovement = false;
	}
	else
	{
		angleDelta = ROTATION_SPEED;
	}

	goalAngle = (int) newDirection;

	setSpeedValues();
	SetBulletDirection(newDirection);
}

void Enemy::SetBulletDirection(DIRECTION direction)
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

void Enemy::InitializeBullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
		mBullets[i]->RegisterPlayerBullets();
	}
}

void Enemy::Update()
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
				//Animation for turning the ship in the correct direction is complete so now move the ship
				currentDirection = newDirection;
				HandleMovement();
			}
			else
			{
				//Animation is not complete so continue animating until it is complete
				HandleMovementAnimation();
			}
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}
}

void Enemy::Render()
{
	if (mAnimating)
	{
		mDeathAnimation->Render();
	}
	if (GetActive())
	{
		mShip->Render();
	}
	PhysicEntity::Render();
}

void Enemy::setSpeedValues()
{
}

void Enemy::HandleMovementAnimation()
{
	int newAngle = currentAngle + angleDelta;

	if (newAngle < 0)
	{
		newAngle += 360;
	}
	else if (newAngle >= 360)
	{
		newAngle %= 360;
	}

	mShip->SetRotation(newAngle);

	currentAngle = newAngle;

	if (currentAngle == goalAngle)
	{
		isAnimatingMovement = false;
	}
}

void Enemy::HandleMovement()
{
}

void Enemy::HandleFiring()
{
}

void Enemy::LoadSpriteSheet(std::string filename)
{
	//Texture* temp = new Texture(filename);

	mShip = new Texture(filename);

	mShip->SetParent(this);

}
