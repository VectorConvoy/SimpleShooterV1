#include "GetPlayerTask.h"

GetPlayerTask::GetPlayerTask()
{
}

GetPlayerTask::GetPlayerTask(Blackboard* blackboard) : super(blackboard)
{

}

GetPlayerTask::GetPlayerTask(Blackboard* blackboard, std::string aName) : super(blackboard, aName)
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
    logText = ("PERFORMING %s TASK", name);
    this->sLogger->Log(logText);

    board->SetPlayer(ScreenManager::Instance()->GetPlayScreen()->GetPlayer());


    if (board->GetPlayer()->GetActive())
    {
        this->controller->FinishWithSuccess();
    }
    else
    {
        this->controller->FinishWithFailure();
    }

}

void GetPlayerTask::Start()
{

    logText = ("STARTING %s TASK", name);
    this->sLogger->Log(logText);
}

void GetPlayerTask::End()
{
    logText = ("ENDING %s TASK", name);
    this->sLogger->Log(logText);
}
