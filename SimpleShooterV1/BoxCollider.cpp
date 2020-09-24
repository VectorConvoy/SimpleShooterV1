#include "BoxCollider.h"

void BoxCollider::AddVertex(int index, Vector2 position)
{
	mVertices[index] = new GameEntity(position);
	
	mVertices[index]->SetParent(this);
}

BoxCollider::BoxCollider(Vector2 size) : Collider(ColliderType::Box)
{
	AddVertex(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVertex(1, Vector2(0.5f * size.x, -0.5f * size.y));
	AddVertex(2, Vector2(-0.5f * size.x, 0.5f * size.y));
	AddVertex(3, Vector2(0.5f * size.x, 0.5f * size.y));

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("BoxCollider.png"));
		mDebugTexture->SetScale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		delete mVertices[i];
		mVertices[i] = nullptr;
	}
}

Vector2 BoxCollider::GetFurthestPoint()
{
	Vector2 localPosition = GetPosition(GameEntity::SPACE::local);

	int furthestIndex = 0;

	float distance = (localPosition + mVertices[0]->GetPosition(GameEntity::SPACE::local)).MagnitudeSquared();

	float otherDistance = 0.0f;

	for (int i = 1; i < MAX_VERTICES; i++)
	{
		otherDistance = (localPosition + mVertices[i]->GetPosition(GameEntity::SPACE::local)).MagnitudeSquared();

		if (otherDistance > distance)
		{
			furthestIndex = i;
			distance = otherDistance;
		}
	}
	return localPosition + mVertices[furthestIndex]->GetPosition(GameEntity::SPACE::local);
}
