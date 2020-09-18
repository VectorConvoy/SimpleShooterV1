#pragma once
#define _SHIPANIMATION_H
#include "texture.h"
#include <vector>
#include "timer.h"

class ShipAnimation {
public:

	enum class DIRECTION { up = 0, right, down, left };

	enum class ANIMATIONDIRECTION {forward = 2, backward = -2};

	const int FRAMES_PER_ROW = 6;
	const int FRAMES_PER_COL = 12;
	const int FRAMES_PER_ANIMATION = 18;
	const int PLAYER_SPEED = 10; //How fast the player should move in pixels



	ShipAnimation(std::string filename, float animationSpeed = 10.0f);
	~ShipAnimation();

	void SetShipMoving(bool moving, DIRECTION newDirection);
	void SetAnimationDone(bool animating);
	void SetDeltaPosition(float deltaX, float deltaY);

	void UpdatePositionForAllTextures(Vector2 position);

	Vector2 newPosition();

	Texture* GetCurrentTexture();
	bool GetShipMoving();
	bool GetAnimationDone();


	void Update();

private:
	Texture* ShipSpriteSheet;
	Texture* CurrentTexture;

	DIRECTION CurrentDirection;
	DIRECTION DestinationDirection;

	int CurrentIndex;
	ANIMATIONDIRECTION animationDirection;
	bool animationDone;
	bool shipMoving; //Used to start or stop the ship based on if a key is being pressed or not
	

	Timer* mTimer;
	Vector2 deltaPosition;

	float mAnimationTimer; //Keep track of our time it has been animating
	float mAnimationSpeed; //Total time to be used by the animation
	float mTimePerFrame; //Time for each frame of the animation to be on screen


	//Store the width and height of a single frame/sprite
	int frameWidth;
	int frameHeight;

	std::vector<SDL_Rect> allAnimationFrames;
	std::vector<Texture*> allAnimationTextures;

	void LoadShipTexture(std::string filename);

};