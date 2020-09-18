#pragma once

#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H

#include "MathHelper.h"

class GameEntity
{
public:
	enum class SPACE { local = 0, world = 1 };

	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	void SetPosition(Vector2 pos);
	Vector2 GetPosition(SPACE space = SPACE::world);

	void SetRotation(float rotation);
	float GetRotation(SPACE space = SPACE::world);

	void SetActive(bool active);
	bool GetActive();

	void SetParent(GameEntity* parent);
	GameEntity* GetParent();

	void Translate(Vector2 vector, SPACE space);

	void Rotate(float amount);

	void SetScale(Vector2 scale);
	Vector2 GetScale(SPACE space = SPACE::world);

	virtual void Update();
	virtual void Render();

private:
	Vector2 mPosition;
	Vector2 mScale;
	float mRotation;


	bool mActive;
	GameEntity* mParent;


};

#endif // !_GAMEENTITY_H
