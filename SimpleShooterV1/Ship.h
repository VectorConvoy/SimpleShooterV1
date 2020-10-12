#pragma once
#define _SHIP_H

#include "AnimatedTexture.h"
#include "Bullet.h"
#include "AudioManager.h"

class Ship : public PhysicEntity
{
public:

	static const int DEFAULT_SPEED = 1;

	Ship();
	~Ship();

	void MoveAnimation();

	void Move(int directionEnumVal);
	void Move(Vector2 directionVector);

	void SetVisible(bool visibility);
	bool GetVisible();

	void SetActive(bool active);
	bool GetActive();

	void SetHit(bool wasHit);
	bool GetHit();

	void SetIsMoving(bool moving);
	bool GetIsMoving();

	void SetShipFileName(std::string filename);
	void SetDirection(float direction);
	void SetDestVector(Vector2 destination);
	
	void Respawn(Vector2 respawnPos);

	void LoadTextureFromFile(std::string filename);
	void LoadTextureFromFile(std::string filename, int x, int y, int w, int h);


	void SetDeathAnimation(std::string filename, int x, int y, int w, int h, int frameCount, float AnimationSpeed, AnimatedTexture::ANIMATED_DIRECTION direction);
	AnimatedTexture* GetDeathAnimation();

	void SetRotationSpeed(float newRotationSpeed);
	void SetRotationSpeed();

	void InitializeBullets();
	void FireBullet();

	void Hit(PhysicEntity* otherEntity);

	void CheckBoundaries();

	void Update();
	void Render();
protected:

	bool mVisible;
	bool mAnimating;
	bool mWasHit;
	bool mActive;
	bool isMoving;

	int frameCounter;

	float spriteAngle;
	float goalAngle;

	float currentDirection;
	float destinationDirection;

	float startTime;
	float animationTimer;
	float animationSpeed; //Speed in seconds

	int angleDelta = DEFAULT_SPEED;

	Vector2 destVector;
	Vector2 mMoveBounds;

	std::string shipTextureFileName;

	//Bullet* mBullets[MAX_BULLETS];

	AudioManager* sAudioManagerInstance;
	Timer* sTimerInstance;

	float mMoveSpeed;

	AnimatedTexture* mDeathAnimation;
	Texture* shipTexture;
};