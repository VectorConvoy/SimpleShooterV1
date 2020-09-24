#pragma once
#define _BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider
{
private:
	static const int MAX_VERTICES = 4;

	GameEntity* mVertices[MAX_VERTICES]; //Allows us to set the parent of the vertices so when the parent rotates, it will also rotate

	void AddVertex(int index, Vector2 position);

public:
	BoxCollider(Vector2 size);
	~BoxCollider();

	Vector2 GetFurthestPoint() override;
};