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
		if (decisionTree->CheckFinished())
		{
			sLoggerInstance->LogDebugText("DECISION TREE FINISHED");
			if (decisionTree->CheckFinishWithSuccess())
			{
				sLoggerInstance->LogDebugText("TREE FINISHED SUCCESS");
				this->Update();
				EnemyMove();
				CheckBoundaries();

				decisionTree->StopBehavior();

				if (!this->mAnimating)
				{				
					//Restart behavior
					sLoggerInstance->LogDebugText("TREE RESET");
					decisionTree->ResetBehavior();
					decisionTree->StartBehavior();

				}

			}

		}
		else if (!decisionTree->CheckStarted())
		{
			sLoggerInstance->LogDebugText("DECISION TREE STARTED");
			decisionTree->StartBehavior();
		}

		while (!decisionTree->CheckFinished() && decisionTree->GetActive())
		{
			decisionTree->DoBehavior();
		}
	}
	else if (this->mAnimating)
	{
		this->Update();
	}
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

	destVector = goalVector * SPEED_MULTIPLIER;

	SetDestVector(destVector);

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

	goalAngle = truncf(goalAngle);
	//Move(destVector);

	//if (goalAngle != spriteAngle)
	//{
	//	mAnimating = true;
	//}
}

void Enemy::EnemyMove()
{

	SetPosition(GetPosition() + destVector);
}

void Enemy::CreateBehaviorTree()
{
	this->sLoggerInstance->Log("CREATING BEHAVIOR TREE FOR ENEMY");

	if (decisionTree != NULL)
	{
		delete decisionTree;
		decisionTree = NULL;
	}

	decisionTree = new BehaviorTree(this);

	//debug
	decisionTree->CreateBehaviorTree();
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

