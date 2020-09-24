#include "Collider.h"

void Collider::SetDebugTexture(Texture* texture)
{
	delete mDebugTexture;

	mDebugTexture = texture;

	mDebugTexture->SetParent(this);
}

Collider::Collider(ColliderType type) : mType(type)
{
	mDebugTexture = nullptr;
}

Collider::~Collider()
{
	if (mDebugTexture)
	{
		delete mDebugTexture;
		mDebugTexture = nullptr;
	}
}

void Collider::Render()
{
	if (DEBUG_COLLIDERS)
	{
		mDebugTexture->Render();
	}
}

Collider::ColliderType Collider::GetType()
{
	return mType;
}
