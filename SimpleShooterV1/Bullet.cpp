#include "Bullet.h"

Bullet::Bullet()
{
	mTimer = Timer::Instance();

	mSpeed = 1000.0f;

	mTexture = new Texture("bullet.png");

	mTexture->SetParent(this);

	mTexture->SetPosition(VEC2_ZERO);

	BulletDirection = VEC2_UP;
	ShipDirection = VEC2_UP;

	Reload();
}

Bullet::~Bullet()
{
	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Bullet::Fire(Vector2 position)
{
	SetPosition(position);
	SetActive(true);
}

void Bullet::Reload()
{
	SetActive(false);

	if ((BulletDirection.x != ShipDirection.x) || (BulletDirection.y != ShipDirection.y))
	{
		BulletDirection = ShipDirection;
	}
}

void Bullet::Update()
{
	if (GetActive())
	{
		Translate(BulletDirection * mSpeed * mTimer->DeltaTime(), GameEntity::SPACE::local);

		Vector2 pos = GetPosition();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER)
		{
			Reload();
		}

		if (pos.x < -OFFSCREEN_BUFFER || pos.x > Graphics::Instance()->SCREEN_WIDTH + OFFSCREEN_BUFFER)
		{
			Reload();
		}

	}
}

void Bullet::Render()
{
	if (GetActive())
	{
		mTexture->Render();
	}
}

Vector2 Bullet::GetBulletDirection()
{
	return BulletDirection;
}

void Bullet::SetBulletDirection(Vector2 vec)
{
	BulletDirection = vec;
}

void Bullet::SetShipDirection(Vector2 vec)
{
	ShipDirection = vec;
}
