#include "Ship.h"
#include <sstream>
static const double DEFAULT_SPEED = 2.0f;


Ship::Ship()
{
	
	animationSpeed = DEFAULT_SPEED;
	AIAnimationTimer = 0.0f;
	invincible = false;
	Health = PLAYER_HEALTH;
	currentRotations = 0;
	futureRotations = 0;
	fullRotation = false;
	angleDelta = DEFAULT_SPEED;
	frameRate = FRAME_RATE;

	mActive = true;

	sLoggerInstance = Logger::Instance();
}

Ship::~Ship()
{
	mActive = false;
	delete shipTexture;
	shipTexture = NULL;
	
	delete mDeathAnimation;
	mDeathAnimation = NULL;
}

void Ship::MoveAnimation()
{
	float angleDelta = 1;

	float remainderGoal;
	float remainderStart;
	
	if (!isPlayer)
	{
		angleDelta = fabsf((float)((goalAngle - spriteAngle)));
		remainderGoal = 0.0f;
		remainderStart = 0.0f;
	}
	else
	{
		angleDelta = 360 / FRAME_RATE * DEFAULT_SPEED;

		//Used to handle situations where direction is halfway i.e. upleft, upright, downleft, downright which are in 45 degree increments and do not divide by 6 evenly
		remainderGoal = fmodf(goalAngle, angleDelta);
		remainderStart = fmodf(spriteAngle, angleDelta);
	}


	if (spriteAngle == 0.0f && goalAngle == 270.0f)
	{
		angleDelta *= -1;
	}
	else if (spriteAngle >= 270.0f && goalAngle == 0.0f)
	{
		angleDelta *= 1;
	}
	else if (spriteAngle > goalAngle)
	{
		angleDelta *= -1;
	}

	//if (!isPlayer)
	//{
	//	printf("AI ANGLE: %f\n", (float) spriteAngle);
	//	printf("AI ANGLE DELTA: %f\n", (float)angleDelta);

	//	printf("AI GOAL ANGLE: %f\n\n", (float) goalAngle);
	//}

	spriteAngle += angleDelta;



	if (spriteAngle >= 360)
	{
		spriteAngle = fmodf(spriteAngle, 360.0f);
	}
	else if (spriteAngle < 0)
	{
		spriteAngle += 360.0f;
	}
	if (goalAngle == spriteAngle)
	{
		mAnimating = false;
	}
	else if (fabsf(goalAngle - spriteAngle) <= remainderGoal && isPlayer)
	{
		mAnimating = false;
		spriteAngle = goalAngle;
	}
	else if (fabsf(goalAngle - spriteAngle) <= remainderStart && isPlayer)
	{
		mAnimating = false;
		spriteAngle = goalAngle;
	}
	//futureRotations = currentRotations;

	SetRotation(spriteAngle);
}

void Ship::AIMoveAnimation()
{

}

void Ship::Move(int directionEnumValue)
{
	if (directionEnumValue == UP)
	{
		Translate(VEC2_UP * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (directionEnumValue == UPRIGHT)
	{
		Translate(VEC2_UPRIGHT * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (directionEnumValue == RIGHT)
	{
		Translate(VEC2_RIGHT * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (directionEnumValue == DOWNRIGHT)
	{
		Translate(VEC2_DOWNRIGHT * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (directionEnumValue == DOWN)
	{
		Translate(VEC2_DOWN * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (directionEnumValue == DOWNLEFT)
	{
		Translate(VEC2_DOWNLEFT * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (directionEnumValue == LEFT)
	{
		Translate(VEC2_LEFT * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
	else if (directionEnumValue == UPLEFT)
	{
		Translate(VEC2_UPLEFT * mMoveSpeed * sTimerInstance->DeltaTime(), GameEntity::SPACE::world);
	}
}

void Ship::Move(Vector2 directionVector)
{
	Translate(directionVector, SPACE::world);
	CheckBoundaries();
}

void Ship::SetVisible(bool visibility)
{
	mVisible = visibility;
}

bool Ship::GetVisible()
{
	return mVisible;
}

void Ship::SetActive(bool active)
{
	mActive = active;
}

bool Ship::GetActive()
{
	return mActive;
}

void Ship::SetAnimating(bool isAnimating)
{
	mAnimating = isAnimating;
}

bool Ship::GetAnimating()
{
	return mAnimating;
}

void Ship::SetHit(bool wasHit)
{
	mWasHit = wasHit;
}

bool Ship::GetHit()
{
	return mWasHit;
}

void Ship::SetIsMoving(bool moving)
{
}

bool Ship::GetIsMoving()
{
	return false;
}

void Ship::SetShipFileName(std::string filename)
{
	shipTextureFileName = filename;
}

void Ship::SetDestVector(Vector2 destination)
{
	//Normalize the vector
	destVector = destination; //Unsure if necessary to normalize

	if (destination == VEC2_ZERO)
	{
		//printf("\n VECTOR IS ZERO \n");
		//goalAngle = spriteAngle;
		
	}
	else
	{
		goalAngle = destinationDirection * 90.0f; //4 Directions which means 360/4 which equals 90 degrees

		//if (spriteAngle != goalAngle && mActive)
		//{
		//	mAnimating = true;
		//}
		//else
		//{
		//	mAnimating = false;
		//}

		if (goalAngle >= 360)
		{
			futureRotations++;
			goalAngle = fmodf(goalAngle, 360.0f);
		}
		else if (goalAngle == 0.0f && spriteAngle == 270.0f)
		{
			futureRotations++;
		}
		else if ((goalAngle == 270.0f && spriteAngle == 0.0f) || (fmodf(spriteAngle, 360.0f) > goalAngle))
		{
			futureRotations--;
		}

	}

	//printf("STATUS: %x\n", mAnimating);
	//printf("SPRITE ANGLE: %f\n", spriteAngle);


}

int Ship::GetHealth()
{
	return Health;
}

void Ship::Respawn(Vector2 respawnPos)
{
	if (!mActive)
	{
		mActive = true;
		SetPosition(respawnPos);
		mVisible = true;
		//Reset position
	}
}

void Ship::LoadTextureFromFile(std::string filename)
{
	shipTexture = new Texture(filename);

	shipTexture->SetParent(this);
}

void Ship::LoadTextureFromFile(std::string filename, int x, int y, int w, int h)
{
	shipTexture = new Texture(filename, x, y, w, h);
	
	shipTexture->SetParent(this);
}

void Ship::SetDeathAnimation(std::string filename, int x, int y, int w, int h, int frameCount, float AnimationSpeed, AnimatedTexture::ANIMATED_DIRECTION direction)
{
	mDeathAnimation = new AnimatedTexture(filename, x, y, w, h, frameCount, AnimationSpeed, direction);
}

AnimatedTexture* Ship::GetDeathAnimation()
{
	return mDeathAnimation;
}

void Ship::SetRotationSpeed(float newRotationSpeed)
{
	angleDelta = newRotationSpeed;
}

void Ship::SetRotationSpeed()
{
	//int frameRate = (animationTimer / sTimerInstance->DeltaTime() / 1000.0f);
}

void Ship::InitializeBullets()
{
	//for (int i = 0; i < MAX_BULLETS; i++)
	//{
	//	mBullets[i] = new Bullet();
	//	mBullets[i]->RegisterPlayerBullets();
	//}
}

void Ship::Hit(PhysicEntity* otherEntity)
{
	if (otherEntity->GetActive())
	{
		if (!invincible)
		{
			if (!mWasHit)
			{
				Health--;
			}
			//Death animation and handling here
			mWasHit = true;


			if ((!mAnimating || !isPlayer) && mActive)
			{
				if (Health <= 0)
				{
					SetActive(false);
					mActive = false;
					mDeathAnimation->ResetAnimation();
					mAnimating = true;
				}
			}

			//Play Death Audio
		}
	}
}

void Ship::CheckBoundaries()
{
	//Check if the ship has hit the boundaries of the screen
	Vector2 position = GetPosition(GameEntity::SPACE::local);

	if (position.x + shipTexture->GetTextureWidth() / 2 > mMoveBounds.x)
	{
		position.x = mMoveBounds.x - shipTexture->GetTextureWidth() / 2;
	}
	else if (position.x - shipTexture->GetTextureWidth() / 2.0f < 0)
	{
		position.x = shipTexture->GetTextureWidth() / 2.0f;
	}

	if (position.y + shipTexture->GetTextureHeight() / 2.0f > mMoveBounds.y)
	{
		position.y = mMoveBounds.y - shipTexture->GetTextureHeight() / 2;
	}
	else if (position.y - shipTexture->GetTextureHeight() / 2.0f < 0)
	{
		position.y = shipTexture->GetTextureHeight() / 2.0f;
	}

	SetPosition(position);
	shipTexture->UpdatePosition((int)position.x, (int)position.y);
}

void Ship::Update()
{
	if (mAnimating)
	{
		sLoggerInstance->LogDebugText("SPRITE IS CURRENTLY ANIMATING");
		if (!mActive)
		{
			if (mWasHit)
			{
				//Reset so the game does not think the ship was hit again
				mWasHit = false;
			}

			sLoggerInstance->LogDebugText("SPRITE IS CURRENTLY ANIMATING FOR DEATH");
			mDeathAnimation->Update();
			mAnimating = mDeathAnimation->IsAnimating();
		}
		//else
		//{
		//	//animationTimer += sTimerInstance->DeltaTime();
		//	//if (animationTimer >= (1 / (animationSpeed * frameRate)))
		//	//{
		//	//	MoveAnimation();

		//	//	animationTimer = 0; //Reset
		//	//}
		//	if (spriteAngle != goalAngle)
		//	{
		//		sLoggerInstance->Log("CHANGING ANGLE TO MATCH GOAL ANGLE");
		//		//SetRotation(goalAngle);
		//		spriteAngle = goalAngle;
		//		SetRotation(spriteAngle);

		//	}
		//}
	}
	else
	{
		//Not being animated
		if (mActive)
		{
			currentDirection = destinationDirection;
			////Check if sprite is facing the correct angle
			//if (spriteAngle != goalAngle)
			//{
			//	sLoggerInstance->Log("ANGLE MISMATCH - SPRITE IS AT AN INCORRECT ANGLE - FIXING.....");
			//	//SetRotation(goalAngle);
			//	spriteAngle = goalAngle;
			//}
			if (spriteAngle != goalAngle)
			{
				sLoggerInstance->Log("CHANGING ANGLE TO MATCH GOAL ANGLE");
				//SetRotation(goalAngle);
				spriteAngle = goalAngle;
				SetRotation(spriteAngle);

			}

			Move(destVector);
		}
	}
}

void Ship::Render()
{
	if (mAnimating)
	{
		if (!mActive)
		{
			mDeathAnimation->Render();
		}
	}

	if (GetActive())
	{
		shipTexture->Render();
	}

	PhysicEntity::Render();
}
