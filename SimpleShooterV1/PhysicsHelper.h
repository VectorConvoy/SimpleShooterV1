#pragma once
#define _PHYSICSHELPER_H

#include "BoxCollider.h"
#include "MathHelper.h"
#include "CircleCollider.h"
//#include "CircleCollider.h

inline bool CircleCollisionCheck(CircleCollider* c1, CircleCollider* c2)
{
	return(c1->GetPosition() - c2->GetPosition()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool ColliderCollisionCheck(Collider* c1, Collider* c2)
{
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle)
	{
		//Do circle to circle collision 

		return CircleCollisionCheck(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else
	{
		return false;
	}
}

class PhysicsHelper
{

};