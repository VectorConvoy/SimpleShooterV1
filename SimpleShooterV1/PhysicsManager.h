#pragma once
#define _PHYSICMANAGER_H

#include "PhysicEntity.h"
#include <bitset>

class PhysicsManager
{
public:

	enum class CollisionLayers
	{
		Friendly = 0, 
		FriendlyProjectiles,
		Enemy,
		EnemyProjectiles,

		//------------------------------
		MaxLayers //Keep track of maximum in case we need to loop through all
	};

	//Use bitset as we can save on space and utilize each bit to determine what enum value it should be
	enum class CollisionFlags
	{
		None = 0x00,
		Friendly = 0x01,
		FriendlyProjectile = 0x02,
		Enemy = 0x04,
		EnemyProjectiles = 0x08
	};

	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysicEntity* entity, CollisionLayers layer);

	void UnregisterEntity(unsigned long ID);

	void Update();

private:
	static PhysicsManager* sInstance;

	//Static Cast so we only cast it on compile time
	std::vector<PhysicEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

	PhysicsManager();
	~PhysicsManager();
};


inline PhysicsManager::CollisionFlags operator |(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator &(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}