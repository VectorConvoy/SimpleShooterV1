#include "GetPlayerTask.h"
#include <sstream>

GetPlayerTask::GetPlayerTask()
{
}

//GetPlayerTask::GetPlayerTask(Blackboard* blackboard) : super(blackboard)
//{
//
//}

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
    std::ostringstream oss;
    oss << "PERFORMING TASK " << name;
    this->sLogger->Log(oss.str());

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
    std::ostringstream oss;
    oss << "STARTING TASK " << name;
    this->sLogger->Log(oss.str());
}

void GetPlayerTask::End()
{
    std::ostringstream oss;
    oss << "ENDING TASK " << name;
    this->sLogger->Log(oss.str());
}
