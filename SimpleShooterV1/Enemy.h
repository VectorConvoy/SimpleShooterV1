#pragma once
#define _ENEMY_H

#include "AnimatedTexture.h"
#include <vector>
#include "Bullet.h"
#include "PhysicEntity.h"

class Enemy : public PhysicEntity
{
public:
	enum class DIRECTION { up = 0, right, down, left };
	enum class ANIMATIONDIRECTION { forward = 1, backward = -1 };

	static const int MAX_BULLETS = 10;
	const std::string ShipName = "enemy1.png";
	const std::string DeathAnimation = "ship_explosion.png";

	Enemy();
	Enemy(std::string filename);
	~Enemy();

	bool IsAnimating();
	bool WasHit();
	Texture* GetTexture();

	void SetAnimationSpeed(float speed = 0.5f);
	void SetMovementSpeed(float speed = 50.0f);
	void SetDirection(DIRECTION direction);
	void SetBulletDirection(DIRECTION direction);

	void Hit(PhysicEntity* other);
	void RespawnEnemy();

	void Update();
	void Render();

		
private:
	Timer* mTimer;

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
