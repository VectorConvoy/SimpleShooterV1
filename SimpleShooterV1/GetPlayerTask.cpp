#include "GetPlayerTask.h"

GetPlayerTask::GetPlayerTask()
{
}

GetPlayerTask::GetPlayerTask(Blackboard* blackboard) : super(blackboard)
{

}

GetPlayerTask::~GetPlayerTask()
{
}

bool GetPlayerTask::CheckConditions()
{
    ScreenManager* instance = ScreenManager::Instance();

    bool isActive = instance->GetPlayScreen()->GetPlayer()->GetActive();

    instance = NULL;
    

    return isActive;
}

void GetPlayerTask::DoAction()
{
    ScreenManager* instance = ScreenManager::Instance();

    board->SetPlayer(instance->GetPlayScreen()->GetPlayer());

    instance = NULL;
}

void GetPlayerTask::Start()
{
    printf("STARTED GETPLAYER TASK\n");
}

void GetPlayerTask::End()
{
    printf("ENDED GETPLAYER TASK\n");
}
