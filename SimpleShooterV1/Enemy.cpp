#include "Enemy.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Blackboard.h"
#include "BehaviorTree.h"
#include <iostream>
#include <sstream>

void Enemy::CustomUpdate()
{
	if (this->mActive)
	{
		if (enemyType->GetDecisionTree()->CheckFinished())
		{
			sLoggerInstance->LogDebugText("DECISION TREE FINISHED");
			if (enemyType->GetDecisionTree()->CheckFinishWithSuccess())
			{
				sLoggerInstance->LogDebugText("TREE FINISHED SUCCESS");
				//this->Update();
				EnemyMove();
				CheckBoundaries();

				enemyType->GetDecisionTree()->StopBehavior();

				if (!this->mAnimating)
				{				
					//Restart behavior
					sLoggerInstance->LogDebugText("TREE RESET");
					enemyType->GetDecisionTree()->ResetBehavior();
					enemyType->GetDecisionTree()->StartBehavior();
				}

			}

		}
		else if (!enemyType->GetDecisionTree()->CheckStarted())
		{
			sLoggerInstance->LogDebugText("DECISION TREE STARTED");
			enemyType->GetDecisionTree()->StartBehavior();
		}

		while (!enemyType->GetDecisionTree()->CheckFinished() && enemyType->GetDecisionTree()->GetActive())
		{
			enemyType->GetDecisionTree()->DoBehavior();
		}
	}

	this->Update();

	for (Bullet* aBullet : mBullets)
	{
		if (aBullet->GetActive())
		{
			aBullet->Update();
		}
	}
}

void Enemy::CustomRender()
{
	this->Render();

	for (Bullet* aBullet : mBullets)
	{
		aBullet->Render();
	}
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

	destVector = goalVector * mMoveSpeed * sTimerInstance->DeltaTime();

	SetDestVector(destVector);
}

void Enemy::SetAngle(float newAngle)
{
	goalAngle = newAngle;
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

	goalAngle = truncf(goalAngle);
	this->shipTexture->SetRotation(goalAngle);	
}

void Enemy::EnemyMove()
{
	SetPosition(GetPosition() + destVector);
}

void Enemy::CreateBehaviorTree()
{
	enemyType->ConstructBehaviorTree();
}

void Enemy::SetEnemyType(EnemyType* typeToSet)
{
	enemyType = typeToSet;

	
}

EnemyType* Enemy::GetEnemyType()
{
	return enemyType;
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

	mDeathAnimation = new AnimatedTexture(DEATH_ANIMATION, 0, 0, 64, 64, 4, 0.5f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this); //Unsure if it will work
	mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	LoadTextureFromFile(SHIP_NAME);

	PhysicEntity::AddCollider(new BoxCollider(shipTexture->ScaledDimensions()));
	InitializeBullets();

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Enemy);

	mActive = false;

	spriteAngle = 180.0f;
	goalAngle = 180.0f;

}

Enemy::Enemy(EnemyType* type)
{
	enemyType = type;
	type->SetEnemyOwner(this);
	sTimerInstance = Timer::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;
	isPlayer = false;
	mActive = true;
	currentDirection = UP;
	destinationDirection = UP;
	spriteAngle = 0;
	Health = type->GetHealth();

	mMoveSpeed = type->GetSpeed();
	mMoveBounds = Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);

	mDeathAnimation = new AnimatedTexture(type->GetDeathAnimationName(), 0, 0, 64, 64, 4, 0.5f, AnimatedTexture::ANIMATED_DIRECTION::vertical);
	mDeathAnimation->SetParent(this); //Unsure if it will work
	//mDeathAnimation->SetPosition(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::WRAP_MODE::once);

	LoadTextureFromFile(type->GetShipFile());

	PhysicEntity::AddCollider(new BoxCollider(shipTexture->ScaledDimensions()));
	InitializeBullets();

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Enemy);

	mActive = false;

	spriteAngle = 180.0f;
	goalAngle = 180.0f;
	SetPosition(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 4));

	enemyType->ConstructBehaviorTree();

}

Enemy::~Enemy()
{
	for (Bullet* aBullet : mBullets)
	{
		delete aBullet;
		aBullet = nullptr;
	}

	mBullets.clear();
}

void Enemy::InitializeBullets()
{
	Bullet* temp;
	for (int i = 0; i < enemyType->GetMaxBullets(); i++)
	{
		temp = new Bullet();
		temp->SetBulletSpeed(enemyType->GetBulletSpeed());
		temp->RegisterEnemyBullets();

		mBullets.push_back(temp);
		
	}
}

void Enemy::SetBulletDirection(Vector2 direction)
{
	for (Bullet* aBullet : mBullets)
	{
		if (!aBullet->GetActive())
		{
			aBullet->SetBulletDirection(direction);
		}
		aBullet->SetShipDirection(direction);
	}
}

bool Enemy::FireBullet()
{
	bool successfulFire = false;

	for (Bullet* aBullet : mBullets)
	{
		if (!aBullet->GetActive())
		{
			sLoggerInstance->Log("ENEMY SHOOT");
			aBullet->Fire(GetPosition());
			//Play audio here
			successfulFire = true;
			break;
		}
	}

	return successfulFire;
}

