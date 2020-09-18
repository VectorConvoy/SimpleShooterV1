#include "ShipAnimation.h"

ShipAnimation::ShipAnimation(std::string filename, float animationSpeed)
{
	mTimer = Timer::Instance();

	LoadShipTexture(filename);

	CurrentTexture = nullptr;
	shipMoving = false;
	animationDone = true;
	CurrentDirection = DIRECTION::up; //Default direction is up
	animationDirection = ANIMATIONDIRECTION::forward;
	deltaPosition = Vector2(); //Vector containing the changes are 0

	Texture* tempTex;

	frameWidth = ShipSpriteSheet->GetTextureWidth() / FRAMES_PER_ROW;
	frameHeight = ShipSpriteSheet->GetTextureHeight() / FRAMES_PER_COL;

	mAnimationSpeed = animationSpeed;

	mTimePerFrame = mAnimationSpeed / FRAMES_PER_ANIMATION;
	mAnimationTimer = 0.0f;

	for (int y = 0; y < FRAMES_PER_COL; y++)
	{
		for (int x = 0; x < FRAMES_PER_ROW; x++)
		{
			tempTex = new Texture(filename, frameWidth * x, frameHeight * y, frameWidth, frameHeight);
			//temp = SDL_Rect{ frameWidth * x, frameHeight * y, frameWidth, frameHeight };
			//allAnimationFrames.push_back(temp);
			allAnimationTextures.push_back(tempTex);
		}
	}

	if (!allAnimationTextures.empty())
	{
		//If there are frames of animation, set the current to be the very first frame.
		CurrentTexture = allAnimationTextures.front();
		CurrentIndex = 0;
	}
}

ShipAnimation::~ShipAnimation()
{
	//for (auto texture : allAnimationTextures)
	//{
	//	delete texture;
	//}

	//allAnimationTextures.clear();

}

void ShipAnimation::SetShipMoving(bool moving, DIRECTION newDirection)
{
	shipMoving = moving;

	DestinationDirection = newDirection;

	if (CurrentDirection == DIRECTION::up && newDirection == DIRECTION::left)
	{
		animationDirection = ANIMATIONDIRECTION::backward;
	}
	else if (CurrentDirection == DIRECTION::left && newDirection == DIRECTION::up)
	{
		animationDirection = ANIMATIONDIRECTION::forward;
	}
	else if (CurrentDirection > newDirection)
	{
		animationDirection = ANIMATIONDIRECTION::backward;
	}
	else if (CurrentDirection != newDirection)
	{
		animationDirection = ANIMATIONDIRECTION::forward;
	}

	CurrentDirection = newDirection;
}

void ShipAnimation::SetAnimationDone(bool animating)
{
	animationDone = animating;
}

void ShipAnimation::SetDeltaPosition(float deltaX, float deltaY)
{
	deltaPosition.x = deltaX;
	deltaPosition.y = deltaY;
}

void ShipAnimation::UpdatePositionForAllTextures(Vector2 position)
{
	for (auto texture : allAnimationTextures)
	{
		texture->SetPosition(position);
	}
}

Vector2 ShipAnimation::newPosition()
{
	float newXPos = CurrentTexture->GetPosition().x + deltaPosition.x * PLAYER_SPEED;
	float newYPos = CurrentTexture->GetPosition().y + deltaPosition.y * PLAYER_SPEED;

	if ((newXPos + frameWidth/2) >= (float) Graphics::SCREEN_WIDTH)
	{
		newXPos = (float) Graphics::SCREEN_WIDTH - frameWidth/2;
	}
	else if ((newXPos - frameWidth / 2) <= 0)
	{
		newXPos = (float) (0 + frameWidth/2);
	}

	if ((newYPos + frameHeight/ 2) >= Graphics::SCREEN_HEIGHT)
	{
		newYPos = (float)Graphics::SCREEN_HEIGHT - frameHeight / 2;
	}
	else if ((newYPos - frameHeight / 2) <= 0)
	{
		newYPos = (float) (0 + frameHeight/2);
	}

	Vector2 newPosition = Vector2(newXPos, newYPos);
	
	UpdatePositionForAllTextures(newPosition);

	return newPosition;
}

Texture* ShipAnimation::GetCurrentTexture()
{
	return CurrentTexture;
}

bool ShipAnimation::GetShipMoving()
{
	return shipMoving;
}

bool ShipAnimation::GetAnimationDone()
{
	return animationDone;
}

void ShipAnimation::Update()
{
	if (!animationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();

		if ((CurrentIndex == (int)DestinationDirection * FRAMES_PER_ANIMATION))
		{

			animationDone = true;
			mAnimationTimer = mAnimationSpeed - mTimePerFrame;	
		}
		else
		{
			CurrentIndex += (int) animationDirection;
			if (CurrentIndex >= (int) allAnimationTextures.size())
			{
				CurrentIndex %= allAnimationTextures.size();
			}
			else if (CurrentIndex < 0)
			{
				//If CurrentIndex is less than 0, go to the end of the vector
				//Mainly used to play an animation in reverse 
				CurrentIndex += (int) allAnimationTextures.size();
			}
		}
		CurrentTexture = allAnimationTextures.at(CurrentIndex);
	}
}

void ShipAnimation::LoadShipTexture(std::string filename)
{
	ShipSpriteSheet = new Texture(filename);
}

