#include "FacePlayerTask.h"

FacePlayerTask::FacePlayerTask()
{
}

FacePlayerTask::FacePlayerTask(Blackboard* blackboard, std::string aName) : super(blackboard, aName)
{

}

FacePlayerTask::~FacePlayerTask()
{
}

bool FacePlayerTask::CheckConditions()
{
	bool check = (board->GetPlayer() != NULL && board->GetEnemy() != NULL) ? true : false;

	if (board->GetMoveDirection() != NULL)
	{
		check = true;
	}
	else
	{
		//ZERO VECTOR IS TREATED AS NULL
		if (board->GetMoveDirection() != VEC2_ZERO)
		{
			check = false;
		}
	}

	return check;
}

void FacePlayerTask::DoAction()
{
	float goalAngle;
	
	goalAngle = (float)(atan2(board->GetMoveDirection().y, board->GetMoveDirection().x) * RAD_TO_DEG) - 90;

	//goalAngle = fmod(goalAngle + (2 * PI), 2 * PI);

	board->GetEnemy()->SetAngle(goalAngle);

	board->GetEnemy()->SetBulletDirection(board->GetMoveDirection());

	this->GetControl()->FinishWithSuccess();

}

void FacePlayerTask::Start()
{
	std::ostringstream oss;

	oss << "STARTING TASK " << name;
	this->sLogger->Log(oss.str());
}

void FacePlayerTask::End()
{
	std::ostringstream oss;

	oss << "ENDING TASK " << name;
	this->sLogger->Log(oss.str());
}
