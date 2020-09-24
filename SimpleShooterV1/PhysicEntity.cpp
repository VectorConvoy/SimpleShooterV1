#include "PhysicEntity.h"
#include "PhysicsHelper.h"
#include "PhysicsManager.h"
void PhysicEntity::AddCollider(Collider* collider, Vector2 localPosition)
{
	collider->SetParent(this);
	collider->SetPosition(localPosition);

	mColliders.push_back(collider);


	if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle)
	{
		float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
		float distance = 0.0f;

		for (int i = 1; i < mColliders.size(); i++)
		{
			distance = mColliders[i]->GetFurthestPoint().Magnitude();

			if (distance > furthestDistance)
			{
				furthestDistance = distance;
			}
		}

		if (mBroadPhaseCollider)
		{
			delete mBroadPhaseCollider;
		}
		mBroadPhaseCollider = new CircleCollider(furthestDistance, true);
		mBroadPhaseCollider->SetParent(this);
		mBroadPhaseCollider->SetPosition(VEC2_ZERO);
	}
}

PhysicEntity::PhysicEntity()
{
	mBroadPhaseCollider = nullptr;

	mId = 0;
}

PhysicEntity::~PhysicEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}

	mColliders.clear();

	if (mBroadPhaseCollider)
	{
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;
	}

	if (mId != 0)
	{
		PhysicsManager::Instance()->UnregisterEntity(mId);
	}
}

void PhysicEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}

	if (mBroadPhaseCollider)
	{
		mBroadPhaseCollider->Render();
	}
}

unsigned long PhysicEntity::GetID()
{
	return mId;
}

bool PhysicEntity::CheckCollision(PhysicEntity* other)
{
	return ColliderCollisionCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
}

void PhysicEntity::Hit(PhysicEntity* other)
{
}
