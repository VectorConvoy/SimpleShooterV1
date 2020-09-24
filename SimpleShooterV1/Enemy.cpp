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

	initializeBullets();

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
	currentDirection = DIRECTION::up;
	newDirection = DIRECTION::up;

	mMoveSpeed = 50.0f;
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
	mDeathAnimation = new AnimatedTexture(DeathAnimation, 0, 0, 64, 64, 4, 0.5f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this);
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	initializeBullets();

	LoadSpriteSheet(filename);

	mShip->SetRotation(180.0);

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

void Enemy::SetAnimationSpeed(float speed)
{
}

void Enemy::SetMovementSpeed(float speed)
{
	mMoveSpeed = speed;
}

void Enemy::SetDirection(DIRECTION direction)
{
}

void Enemy::SetBulletDirection(DIRECTION direction)
{
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
			//if (!isAnimatingMovement)
			//{
			//	currentDirection = newDirection;
			//	HandleMovement();
			//}
			//else
			//{
			//	HandleMovementAnimation();
			//}

			//HandleFiring();
		}
	}

	//for (int i = 0; i < MAX_BULLETS; i++)
	//{
	//	mBullets[i]->Update();
	//}
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

void Enemy::initializeBullets()
{
}

void Enemy::setSpeedValues()
{
}

void Enemy::HandleMovementAnimation()
{
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
