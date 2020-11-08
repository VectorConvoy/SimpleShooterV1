#pragma once
#define _PLAYER_H

#include "Ship.h"
#include "InputManager.h"
#include "Bullet.h"

class Player : public Ship
{
public:

	const std::string SHIP_NAME = "SpriteSheet.png";
	const std::string DEATH_ANIMATION = "ship_explosion.png";
	const static int MAX_BULLETS = 10;
	const static int INVINCIBILITY_TIME = 3; //In seconds

	const static int DEFAULT_SPEED = 400;

	const int FRAME_HEIGHT = 64;
	const int FRAME_WIDTH = 64;

	Player();
	~Player();

	void InitializeBullets();
	void SetBulletDirection(float nextDirection);
	void FireBullet();

	void CustomUpdate();
	void CustomRender();

	void RespawnPlayer();
	void CheckKeyInput();
	void SetPlayerDirection(float direct);

	void SetPlayerMoving(bool isMoving);
	void InvinicibilityFlash();


private:
	
	Bullet* mBullets[MAX_BULLETS];
	InputManager* mInputManager;

	float mInvincibleTimer;
	bool PlayerMoving;

	

};