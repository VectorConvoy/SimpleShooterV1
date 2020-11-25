/*
* A class to handle AI functions and
* all the enemies
* 
* Mainly used to keep track of all the enemies
* Unsure if needed
* 
*/
#include "AIEngine.h"
#include "FleeBehavior.h"
#include "IdleBehavior.h"
#include "SeekBehavior.h"
#include "ShootBehavior.h"
#include <algorithm>

AIEngine* AIEngine::sInstance = NULL;

AIEngine* AIEngine::Instance()
{
    if (sInstance == NULL)
    {
        sInstance = new AIEngine();
    }

    return sInstance;
}

void AIEngine::Release()
{
    delete sInstance;
    sInstance = NULL;
}

void AIEngine::SetPlayer(Player* thePlayer)
{
    player = thePlayer;
}

void AIEngine::AddEnemy(std::shared_ptr<Enemy> enemy)
{
    //EnemyType* newType = new EnemyType();
    //
    //enemy.get()->SetEnemyType(newType);

    enemies.push_back(enemy);
}

void AIEngine::RemoveEnemy(std::shared_ptr<Enemy> enemy)
{
    enemies.erase(std::find(enemies.begin(), enemies.end() - 1, enemy));
}

void AIEngine::ClearEnemies()
{
    for (std::shared_ptr<Enemy> anEnemy : enemies)
    {
        anEnemy.reset();
    }
}

void AIEngine::InitializeBehaviors()
{
    //FleeBehavior* tempFlee = new FleeBehavior();
    std::shared_ptr<Behavior> tempFlee = std::shared_ptr<Behavior>(new FleeBehavior());
    std::shared_ptr<Behavior> tempSeek = std::shared_ptr<Behavior>(new SeekBehavior());
    std::shared_ptr<Behavior> tempShoot = std::shared_ptr<Behavior>(new ShootBehavior());
    std::shared_ptr<Behavior> tempIdle = std::shared_ptr<Behavior>(new IdleBehavior());

    //Construct each behavior
    tempFlee.get()->ConstructBehavior();
    tempSeek.get()->ConstructBehavior();
    tempShoot.get()->ConstructBehavior();
    tempIdle.get()->ConstructBehavior();

    //Move the pointers into the vector
    allBehaviors.push_back(std::move(tempFlee));
    allBehaviors.push_back(std::move(tempSeek));
    allBehaviors.push_back(std::move(tempShoot));
    allBehaviors.push_back(std::move(tempIdle));

}

std::vector<std::shared_ptr<Behavior>> AIEngine::GetAllBehaviors()
{
    return allBehaviors;
}

Behavior* AIEngine::GetSpecificBehavior(std::string name)
{
    for (std::shared_ptr<Behavior> aBehavior : allBehaviors)
    {
        if (aBehavior.get()->GetName() == name)
        {
            return aBehavior.get();
        }
    }

    return nullptr;
}

void AIEngine::SortBehaviors()
{
    //Sort the behaviors via priority
    std::sort(allBehaviors.begin(), allBehaviors.end());
}

void AIEngine::SetPriorityForBehavior(std::string name, int priorityVal)
{
    for (std::shared_ptr<Behavior> aBehavior : allBehaviors)
    {
        if (aBehavior.get()->GetName() == name)
        {
            aBehavior.get()->SetPriorityID(priorityVal);
            break;
        }
    }
}

void AIEngine::SetValueForBehavior(std::string name, float val)
{
    for (std::shared_ptr<Behavior> aBehavior : allBehaviors)
    {
        if (aBehavior.get()->GetName() == name)
        {
            aBehavior.get()->SetValue(val);
            break;
        }
    }
}

void AIEngine::SetConditionTypeForBehavior(std::string name, std::string condType)
{
    for (std::shared_ptr<Behavior> aBehavior : allBehaviors)
    {
        if (aBehavior.get()->GetName() == name)
        {
            aBehavior.get()->SetConditionType(condType);
            break;
        }
    }
}

void AIEngine::ClearBehaviors()
{
    for (std::shared_ptr<Behavior> aBehavior: allBehaviors)
    {
        aBehavior.reset();
    }
}

void AIEngine::Update()
{

}

AIEngine::AIEngine()
{
    
}

AIEngine::~AIEngine()
{

}
