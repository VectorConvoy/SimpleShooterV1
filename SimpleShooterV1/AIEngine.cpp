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
    //Initialize AI Behaviors and Decision Trees
    for (Enemy* enemy : enemies)
    {

    }
}

AIEngine::AIEngine()
{
    sInstance = AIEngine::Instance();
}

AIEngine::~AIEngine()
{

}
