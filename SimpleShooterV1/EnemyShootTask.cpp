#include "EnemyShootTask.h"
#include <sstream>

//EnemyShootTask::EnemyShootTask(Blackboard* board) : super(board)
//{
//
//}

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
	std::ostringstream oss;
	oss << "STARTING TASK " << name;
	this->sLogger->Log(oss.str());
}

void EnemyShootTask::End()
{
	std::ostringstream oss;
	oss << "ENDING TASK " << name;
	this->sLogger->Log(oss.str());
}

void EnemyShootTask::DoAction()
{
	bool fire = board->GetEnemy()->FireBullet();
	std::ostringstream oss;
	oss << name;

	if (fire)
	{
		oss << " FIRED SUCESSFULLY";
		this->GetControl()->FinishWithSuccess();
	}
	else
	{
		oss << " FAILED";
		this->GetControl()->FinishWithFailure();
	}

	this->sLogger->Log(oss.str());
}
