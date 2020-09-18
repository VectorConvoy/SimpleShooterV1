#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;

	mRotation = 0.0f;
	mActive = true;
	mParent = nullptr;

	mScale = VEC2_ONE;
}

GameEntity::~GameEntity()
{
	mParent = NULL;
}

void GameEntity::SetPosition(Vector2 pos)
{
	mPosition = pos;
}

Vector2 GameEntity::GetPosition(SPACE space)
{
	if (space == SPACE::local || mParent == NULL)
	{
		return mPosition;
	}

	Vector2 parentScale = mParent->GetScale(SPACE::world);
	Vector2 scaled = Vector2(mPosition.x * parentScale.x, mPosition.y * parentScale.y);
	Vector2 rotPos = RotateVector(scaled, mParent->GetRotation(SPACE::local));

	return mParent->GetPosition(SPACE::world) + rotPos;
}

void GameEntity::SetRotation(float rotation)
{
	mRotation = rotation;

	if (mRotation > 360.0f)
	{
		float mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}
	else if (mRotation < 0.0f)
	{
		float mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}

float GameEntity::GetRotation(SPACE space)
{
	if (space == SPACE::local || mParent == NULL)
	{
		return mRotation;
	}
	return mParent->GetRotation(SPACE::world) + mRotation;
}

void GameEntity::SetActive(bool active)
{
	mActive = active;
}

bool GameEntity::GetActive()
{
	return mActive;
}

void GameEntity::SetParent(GameEntity* parent)
{
	if (parent == NULL)
	{
		mPosition = GetPosition(SPACE::world);
		mRotation = GetRotation(SPACE::world);
		mScale = GetScale(SPACE::world);
	}
	else 
	{
		if (mParent != NULL)
		{
			SetParent(NULL);
		}

		Vector2 parentScale = parent->GetScale(SPACE::world);

		Vector2 DeltaPosition = (GetPosition(SPACE::world) - parent->GetPosition(SPACE::world));

		mPosition = RotateVector(DeltaPosition, -parent->GetRotation(SPACE::world));

		mPosition.x /= parentScale.x;
		mPosition.x /= parentScale.x;
		mPosition.y /= parentScale.y;

		mRotation -= parent->GetRotation(SPACE::world);

		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

GameEntity* GameEntity::GetParent()
{
	return mParent;
}

void GameEntity::Translate(Vector2 vector, SPACE space)
{
	if (space == GameEntity::SPACE::world)
	{
		mPosition += vector;
	}
	else
	{
		mPosition += RotateVector(vector, GetRotation());
	}
}

void GameEntity::Rotate(float amount)
{
	mRotation += amount;
}

void GameEntity::SetScale(Vector2 scale)
{
	mScale = scale;
}

Vector2 GameEntity::GetScale(SPACE space)
{
	if (space == SPACE::local || mParent == NULL)
	{
		return mScale;
	}

	Vector2 scale = mParent->GetScale(SPACE::world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{
}
