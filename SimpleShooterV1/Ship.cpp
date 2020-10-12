#include "Ship.h"

Ship::Ship()
{
	animationSpeed = DEFAULT_SPEED;
}

Ship::~Ship()
{
}

void Ship::MoveAnimation()
{
	float angleDelta = (float)(animationTimer / (animationSpeed / (goalAngle - spriteAngle)));
	
	int rotationDirection = (goalAngle - spriteAngle);
	
	if (rotationDirection != 0)
	{
		rotationDirection /= rotationDirection; //We only want the sign (positive or negative)
	}

	angleDelta *= rotationDirection;

	spriteAngle += angleDelta;

	//TO-DO
	//Look into figuring out how to reduce the angle delta so that it starts off small and increases. Currently, it works when the animation timer is low enough

	//printf("***********************************************\nANGLE DELTA BEFORE MULTIPLIED: %f\n***********************************************\n", (float)angleDelta);

	//printf("***********************************************\nANIMATION TIMER: %f\n***********************************************\n", (float)animationTimer);

	//printf("***********************************************\nROTATION DIRECTION: %f\n***********************************************\n", (float)rotationDirection);


	//printf("***********************************************\nANGLE DELTA: %f\n***********************************************\n", (float)angleDelta);

	//printf("***********************************************\nCURRENT ANGLE: %f\n***********************************************\n",(float)spriteAngle);

	if (fabsf(goalAngle-spriteAngle) < 1.0f)
	{
		mAnimating = false;
	}

	SetRotation(spriteAngle);
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

void Ship::SetDirection(float direction)
{

}

void Ship::SetDestVector(Vector2 destination)
{
	//Normalize the vector
	destVector = destination; //Unsure if necessary to normalize

	if (destination == VEC2_ZERO)
	{
		goalAngle = spriteAngle;
		
	}
	else
	{
		
		goalAngle = destinationDirection * 90.0f; //4 Directions which means 360/4 which equals 90 degrees

		if (spriteAngle != goalAngle)
		{
			mAnimating = true;
		}
		else
		{
			mAnimating = false;
		}

		if (spriteAngle > goalAngle)
		{
			angleDelta *= -1;
		}
	}



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

void Ship::FireBullet()
{
	//for (int i = 0; i < MAX_BULLETS; i++)
	//{
	//	if (!mBullets[i]->GetActive())
	//	{
	//		mBullets[i]->Fire(GetPosition());

	//		//Play audio here

	//		break;

	//	}
	//}
}

void Ship::Hit(PhysicEntity* otherEntity)
{
	//Death animation and handling here
	mWasHit = true;

	if (!mAnimating && mActive)
	{
		mActive = false;
		mDeathAnimation->ResetAnimation();
		mAnimating = true;

	}

	//Play Death Audio
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
		if (!mActive)
		{
			if (mWasHit)
			{
				//Reset so the game does not think the ship was hit again
				mWasHit = false;
			}

			mDeathAnimation->Update();
			mAnimating = mDeathAnimation->IsAnimating();
		}
		else
		{
			animationTimer += sTimerInstance->DeltaTime();
			MoveAnimation();

			if (animationTimer >= animationSpeed)
			{
				mAnimating = false;
				animationTimer = 0; //Reset
			}
		}
	}
	else
	{
		//Not being animated
		if (mActive)
		{
			currentDirection = destinationDirection;
			//Check if sprite is facing the correct angle
			if (spriteAngle != goalAngle)
			{
				//SetRotation(goalAngle);
				spriteAngle = goalAngle;
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

	++frameCounter;
}
