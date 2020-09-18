#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIMATED_DIRECTION animationDirection) : Texture(filename, x, y, w, h)
{
	mTimer = Timer::Instance();
	
	mStartX = x;
	mStartY = y;

	mFrameCount = frameCount;
	mAnimationSpeed = animationSpeed;
	mTimePerFrame = mAnimationSpeed / mFrameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animationDirection;

	mAnimationDone = false;

	mWrapMode = loop;

}

AnimatedTexture::~AnimatedTexture()
{

}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	mWrapMode = mode;
}

void AnimatedTexture::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();

		if (mAnimationTimer >= mAnimationSpeed)
		{
			if (mWrapMode == loop)
			{
				mAnimationTimer -= mAnimationSpeed;
			}
			else
			{
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}
		if (mAnimationDirection == forward)
		{
			mClippedRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;

			//Divide by 2 because the default point is the center of the sprite
			if (mClippedRect.x + (mClippedRect.w/2) >= mWidth)
			{
				//If we reached the end of the row, we need to reset x position while also moving down a row using the y position
				mClippedRect.x = 0;
				mClippedRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
				
				if (mClippedRect.y + (mClippedRect.h/2) >= mHeight)
				{
					mClippedRect.y = 0;

				}
			}
		}
		else if (mAnimationDirection == horizontal)
		{
			mClippedRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
		}
		else
		{
			mClippedRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}
