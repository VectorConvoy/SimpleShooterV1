#pragma once
#define _PLAYER_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <vector>
#include "Bullet.h"

class Player : public PhysicEntity
{
public:

	enum class DIRECTION { up = 0, right, down, left };
	enum class ANIMATIONDIRECTION { forward = 1, backward = -1 };


	static const int MAX_BULLETS = 10;
	const int FRAMES_PER_ANIMATION = 18;
	const int FRAMES_PER_ROW = 6;
	const int FRAMES_PER_COL = 12;

	const std::string ShipName = "SpriteSheet.png";
	const std::string DeathAnimation = "ship_explosion.png";

	Player();
	Player(std::string filename);
	~Player();

	void Visible(bool visible);
	
	void Hit(PhysicEntity* other) override;
	bool WasHit();

	bool IsAnimating();
	Texture* GetTexture();

	void SetAnimationSpeed(float speed = 0.5f);
	void SetDirection(DIRECTION direction);
	void SetBulletDirection(DIRECTION direction);

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

	DIRECTION currentDirection;
	DIRECTION newDirection;
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
	//Texture* shipSpriteSheet;

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