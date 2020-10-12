#include "AIEngine.h"

#include "SteeringBehaviors.h"


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

void AIEngine::ActivateAI()
{
    //SteeringBehavior behaviors;
    //Vector2 newTarget;
    ////Initialize AI Behaviors and Decision Trees
    //for (Enemy* enemy : enemies)
    //{
    //    newTarget = behaviors.Flee(enemy->GetPosition(), player->GetPosition(), 1000.0f);
    //    enemy->SetTargetVector(newTarget);

    //   /* printf("New Target Vector: <%f, %f>\n", newTarget.x, newTarget.y);*/
    //}
}

void AIEngine::SetPlayer(Player* thePlayer)
{
    player = thePlayer;
}

void AIEngine::AddEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

void AIEngine::Update()
{
    for (Enemy* enemy : enemies)
    {
        newTarget = behaviors.Seek(enemy->GetPosition(), player->GetPosition());
        enemy->SetEnemyDestVector(newTarget);
        enemy->Update();
    }

    ActivateAI();
}

AIEngine::AIEngine()
{
    
}

AIEngine::~AIEngine()
{

}
