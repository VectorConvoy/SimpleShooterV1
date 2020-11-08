#pragma once
#define _SHIP_H

#include "AnimatedTexture.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "Logger.h"

class ScreenManager;

class Ship : public PhysicEntity
{
public:
	static const int FRAME_RATE = 60;
	const static int PLAYER_HEALTH = 5;

	Ship();
	~Ship();

	void MoveAnimation();
	void AIMoveAnimation();

	void Move(int directionEnumVal);
	void Move(Vector2 directionVector);

	void SetVisible(bool visibility);
	bool GetVisible();

	void SetActive(bool active);
	bool GetActive();

	void SetAnimating(bool isAnimating);
	bool GetAnimating();

	void SetHit(bool wasHit);
	bool GetHit();

	void SetIsMoving(bool moving);
	bool GetIsMoving();

	void SetShipFileName(std::string filename);
	void SetDirection(float direction);
	void SetDestVector(Vector2 destination);

	int GetHealth();

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
	bool invincible;
	bool isPlayer;
	bool fullRotation;

	int frameRate;
	int Health;
	int futureRotations;  //Use to keep track of the change in rotations without committing yet
	int currentRotations; //Keep track of number of rotation

	float spriteAngle;
	float goalAngle;

	float currentDirection;
	float destinationDirection;

	float startTime;
	float animationTimer;
	float AIAnimationTimer;
	float animationSpeed; //Speed in seconds

	int angleDelta;

	Vector2 destVector;
	Vector2 mMoveBounds;

	std::string shipTextureFileName;

	//Bullet* mBullets[MAX_BULLETS];

	ScreenManager* sScreenManagerInstance;
	AudioManager* sAudioManagerInstance;
	Timer* sTimerInstance;
	Logger* sLoggerInstance;

	float mMoveSpeed;

	AnimatedTexture* mDeathAnimation;
	Texture* shipTexture;
};