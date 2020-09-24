#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::sInstance = nullptr;

PhysicsManager* PhysicsManager::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new PhysicsManager();
    }
    return sInstance;
}

void PhysicsManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

/*Function to create a bitset with the appropriate value depending on the flag*/
void PhysicsManager::SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags)
{
    //Make a bit set that is a size of Max Layers which is 4
    mLayerMasks[static_cast<unsigned int>(layer)] = std::bitset <static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(flags));
}

unsigned long PhysicsManager::RegisterEntity(PhysicEntity* entity, CollisionLayers layer)
{
    //Add the entity to the correct layer
    mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);
    mLastId++;
    //ID cannot be 0 so we can use this to determine if an entity is registered or not
    return mLastId;
}

void PhysicsManager::UnregisterEntity(unsigned long ID)
{
    bool found = false;

    //Outer loop used to interatre through each layer
    for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !found; i++)
    {
        //Inner loop used to interate through all IDs of each layer
        for (int j = 0; j < mCollisionLayers[i].size() && !found; j++)
        {
            if (mCollisionLayers[i][j]->GetID() == ID)
            {
                //We use erase and begin to delete the correct entity
                mCollisionLayers[i].erase(mCollisionLayers[i].begin() + j);
                found = true;
            }
        }
    }

}

void PhysicsManager::Update()
{
    //Collision Detection here
    for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
    {
        for (unsigned int j = 0; j < static_cast<unsigned int>(CollisionLayers::MaxLayers); j++)
        {
            //Loop through each layer twice

            //Test the bitsets and see if they collide
            if (mLayerMasks[i].test(j) && i <= j)
            {
                //Now we need to check the collisions against each other's vector's
                for (unsigned k = 0; k < mCollisionLayers[i].size(); k++)
                {
                    for (unsigned int l = 0; l < mCollisionLayers[j].size(); l++)
                    {
                        //Check if two of the layers have collided with each other

                        if (mCollisionLayers[i][k]->CheckCollision(mCollisionLayers[j][l]))
                        {
                            //There is a collision if we get here

                            mCollisionLayers[i][k]->Hit(mCollisionLayers[j][l]);
                            mCollisionLayers[j][l]->Hit(mCollisionLayers[i][k]);
                        }
                    }
                }
            }
        }
    }
}

PhysicsManager::PhysicsManager()
{
    mLastId = 0;

    //Loop used to Initializing the masks. Masks start as None so none of them can interact with each other at first
    for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
    {
        mLayerMasks[i] = std::bitset <static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(CollisionFlags::None));
    }
}

PhysicsManager::~PhysicsManager()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
    {
        mCollisionLayers[i].clear();
    }
}
