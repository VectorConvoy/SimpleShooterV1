#pragma once
#define _PLAYEROLD_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <vector>
#include "Bullet.h"

class PlayerOLD : public PhysicEntity
{
public:

	enum class DIRECTION { up = 0, right, down, left };
	enum class ANIMATIONDIRECTION { forward = 1, backward = -1 };

	static const int MAX_BULLETS = 10;
	const int FRAMES_PER_ANIMATION = 18;
	const int FRAMES_PER_ROW = 6;
	const int FRAMES_PER_COL = 12;
	const int ANIMATION_RATE = 6;

	const std::string ShipName = "SpriteSheet.png";
	const std::string DeathAnimation = "ship_explosion.png";

	PlayerOLD();
	PlayerOLD(std::string filename);
	~PlayerOLD();

	void Visible(bool visible);
	
	void Hit(PhysicEntity* other) override;
	bool WasHit();

	bool IsAnimating();
	Texture* GetTexture();

	void SetAnimationSpeed(float speed = 0.1f);
	void SetDirection(float nextDirection);
	void SetBulletDirection(float nextDirection);

	void RespawnPlayer();

	void Update();
	void Render();


private:

	Timer* mTimer;
	InputManager* mInput;
	//AudioManager* mAudio

	bool mVisible;
	bool mAnimating;
	bool animationDone;
	bool mWasHit;

	bool isAnimatingMovement;

	float currentDirection;
	float newDirection;
	int frameWidth;
	int frameHeight;

	 
	int mFrameCount;
	int currentIndex;
	int goalIndex;
	int indexDelta;

	std::vector<SDL_Rect> allAnimationSpritesClipped;
	std::vector< std::pair<int, int> > rectCoordinates;
	
	Texture* mShip;
	AnimatedTexture* mDeathAnimation;

	float startTime;
	float timePerFrame;
	float animationSpeed; 
	float animationTimer; //Keep track of our time it has been animating

	float mMoveSpeed;
	Vector2 mMoveBounds;

	Bullet* mBullets[MAX_BULLETS];

	void initializeBullets();
	void setSpeedValues();

	void HandleMovementAnimation();
	void HandleMovement();
	void HandleFiring();

	void LoadSpriteSheet(std::string filename);

};