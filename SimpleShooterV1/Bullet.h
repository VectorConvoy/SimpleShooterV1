#pragma once
#define _BULLET_H

#include "PhysicEntity.h"
#include "timer.h"

class Bullet : public PhysicEntity
{
public:
	
	Bullet();
	~Bullet();

	void Fire(Vector2 position);
	void Reload();

	Vector2 GetBulletDirection();
	
	void SetBulletDirection(Vector2 vec);
	void SetShipDirection(Vector2 vec);
	void RegisterPlayerBullets();

	void Update();
	void Render();

private:
	const float OFFSCREEN_BUFFER = 14.0f;
	
	Timer* mTimer;

	Vector2 BulletDirection;
	Vector2 ShipDirection;
	
	float mSpeed;
	Texture* mTexture;


};
