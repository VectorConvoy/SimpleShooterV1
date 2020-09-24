#pragma once
#define _ANIMATEDTEXTURE_H

#include "timer.h"
#include "texture.h"

class AnimatedTexture : public Texture
{
public:
	enum WRAP_MODE { once = 0, loop = 1};
	enum ANIMATED_DIRECTION {horizontal = 0, vertical = 1, forward = 2}; //Forward is where the animation spans between multiple rows 

	AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIMATED_DIRECTION animationDirection);
	~AnimatedTexture();


	void WrapMode(WRAP_MODE mode);

	void ResetAnimation();
	bool IsAnimating();

	void Update();

private:
	Timer* mTimer;

	int mStartX;
	int mStartY;

	float mAnimationTimer; //Keep track of our time it has been animating
	float mAnimationSpeed; //Total time to be used by the animation
	float mTimePerFrame; //Time for each frame of the animation to be on screen

	int mFrameCount;

	WRAP_MODE mWrapMode;
	ANIMATED_DIRECTION mAnimationDirection;

	bool mAnimationDone; //Check if animation is done
};