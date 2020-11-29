#include "FaceAwayPlayerTask.h"

FaceAwayPlayerTask::FaceAwayPlayerTask(Blackboard* board, std::string aName) : super(board, aName)
{
}

FaceAwayPlayerTask::~FaceAwayPlayerTask()
{
}

bool FaceAwayPlayerTask::CheckConditions()
{
	bool check = (board->GetPlayer() != NULL && board->GetEnemy() != NULL);

	return check;
	return check;
}

void FaceAwayPlayerTask::Start()
{
	std::ostringstream oss;
	oss << "STARTING TASK " << name;
	this->sLogger->Log(oss.str());
}

void FaceAwayPlayerTask::End()
{
	std::ostringstream oss;
	oss << "ENDING TASK " << name;
	this->sLogger->Log(oss.str());
}

void FaceAwayPlayerTask::DoAction()
{
	float goalAngle;

	goalAngle = (atan2(board->GetMoveDirection().y, board->GetMoveDirection().x) * RAD_TO_DEG) + 90.0f;

	board->GetEnemy()->SetAngle(goalAngle);

	board->GetEnemy()->SetBulletDirection(board->GetMoveDirection());

	this->GetControl()->FinishWithSuccess();
}
