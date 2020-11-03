#include "EnemyShootTask.h"

EnemyShootTask::EnemyShootTask(Blackboard* board) : super(board)
{

}

EnemyShootTask::EnemyShootTask(Blackboard* board, std::string aName) : super(board, aName)
{
}

EnemyShootTask::~EnemyShootTask()
{
}

bool EnemyShootTask::CheckConditions()
{
	bool check = (board->GetEnemy() != NULL) ? true : false;

	return check;
}

void EnemyShootTask::Start()
{
	logText = ("STARTING %s TASK", name);
	this->sLogger->Log(logText);
}

void EnemyShootTask::End()
{
	logText = ("ENDING %s TASK", name);
	this->sLogger->Log(logText);
}

void EnemyShootTask::DoAction()
{
	bool fire = board->GetEnemy()->FireBullet();

	if (fire)
	{
		this->GetControl()->FinishWithSuccess();
	}
	else
	{
		this->GetControl()->FinishWithFailure();
	}
}
