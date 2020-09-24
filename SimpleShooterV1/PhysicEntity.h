#pragma once
#define _PHYSICENTITY_H

#include "Collider.h"
#include <vector>

class PhysicEntity : public GameEntity
{
protected:

	unsigned long mId;

	Collider* mBroadPhaseCollider;

	std::vector<Collider*> mColliders; //Vector in case a single collider shape cannot accurately encompass a sprite

	void AddCollider(Collider* collider, Vector2 localPosition = VEC2_ZERO);



public:
	PhysicEntity();
	virtual ~PhysicEntity();
	virtual void Render();

	unsigned long GetID();

	bool CheckCollision(PhysicEntity* other);

	virtual void Hit(PhysicEntity* other);
};