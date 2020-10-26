#include "MoveToTask.h"

MoveToTask::MoveToTask(Blackboard* board)
{
	super(enemyBoard);

}

MoveToTask::~MoveToTask()
{
}

bool MoveToTask::CheckConditions()
{
	bool check = board->GetEnemy()->GetActive();


	return check;
}

void MoveToTask::Start()
{
	printf("STARTED MOVE TO TASK\n");
}

void MoveToTask::End()
{
	printf("STARTED MOVE TO TASK\n");
}

void MoveToTask::DoAction()
{
	board->GetEnemy()->SetEnemyDestVector(board->GetMoveDirection());

}
