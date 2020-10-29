#include "AIEngine.h"

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

void AIEngine::AddEnemy(std::shared_ptr<Enemy> enemy)
{
    enemies.push_back(enemy);
}

void AIEngine::RemoveEnemy(std::shared_ptr<Enemy> enemy)
{
    enemies.erase(std::find(enemies.begin(), enemies.end() - 1, enemy));
}

void AIEngine::Update()
{
    //for (std::shared_ptr<Enemy> enemy : enemies)
    //{
    //    if (enemy->GetDebugBehavior() == BEHAVIOR::flee)
    //    {
    //        newTarget = behaviors.Flee(enemy->GetPosition(), player->GetPosition(), 1000.0f);
    //    }
    //    else
    //    {
    //        newTarget = behaviors.Wander(enemy->GetPosition(), player->GetPosition());
    //    }
    //    enemy->SetEnemyDestVector(newTarget);
    //    //enemy->Update();
    //}

    //ActivateAI();
}

AIEngine::AIEngine()
{
    
}

AIEngine::~AIEngine()
{

}
