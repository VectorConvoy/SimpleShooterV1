#include "Enemy.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Enemy::CustomUpdate()
{
	this->Update();
	EnemyMove();
	CheckBoundaries();
}

void Enemy::CustomRender()
{
	this->Render();
}

void Enemy::SetDebugBehavior(int behavior)
{
	debug_behavior = behavior;
}

int Enemy::GetDebugBehavior()
{
	return debug_behavior;
}

void Enemy::RespawnEnemy()
{
	this->Respawn(Vector2(Graphics::SCREEN_WIDTH / 4, Graphics::SCREEN_HEIGHT / 4));
}

void Enemy::SetEnemyDestVector(Vector2 goalVector)
{
	destVector = goalVector;

	Vector2 normal = destVector.Normalized();

	SetDestVector(goalVector);

	goalAngle = (float)(atan2(goalVector.y, goalVector.x) * RAD_TO_DEG) + 90;
	//goalAngle = fmodf(goalAngle + 2 * PI, 2 * PI);
	
	if (goalAngle < 0)
	{
		goalAngle += 360;
		futureRotations--;
	}
	else if (goalAngle > 360)
	{
		futureRotations++;
		goalAngle = fmodf(goalAngle, 360);
	}

	

	printf("GOAL ANGLE: %f\n", goalAngle);
	//Move(destVector);

}

void Enemy::EnemyMove()
{
	SetPosition(GetPosition() + destVector);
}

Enemy::Enemy()
{
	sTimerInstance = Timer::Instance();
	
	mVisible = false;
	mAnimating = false;
	mWasHit = false;
	isPlayer = false;
	mActive = true;
	currentDirection = UP;
	destinationDirection = UP;
	spriteAngle = 0;
	Health = 1;

	mMoveSpeed = 50.0f;
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);

	mDeathAnimation = new AnimatedTexture(DEATH_ANIMATION, 0, 0, 64, 64, 4, 1.0f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this); //Unsure if it will work
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	LoadTextureFromFile(SHIP_NAME);

	PhysicEntity::AddCollider(new BoxCollider(shipTexture->ScaledDimensions()));
	InitializeBullets();

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Enemy);

	mActive = false;

	spriteAngle = 180.0f;
}

Enemy::~Enemy()
{

}

void Enemy::InitializeBullets()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
		mBullets[i]->RegisterPlayerBullets();
	}
}

