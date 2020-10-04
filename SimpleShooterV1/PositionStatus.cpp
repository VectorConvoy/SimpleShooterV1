#include "PositionStatus.h"

void PositionStatus::SetCloseToPlayer(float minDeltaDistance)
{
	if (distanceFromPlayer <= minDeltaDistance)
	{
		closeToPlayer = true;
	}
	else
	{
		closeToPlayer = false;
	}
}

Vector2 PositionStatus::GetVectorDistanceFromPlayer(Vector2 playerPosition, Vector2 enemyPosition)
{
	float deltaX;
	float deltaY;

	deltaX = fabs(playerPosition.x - enemyPosition.x);
	deltaY = fabs(playerPosition.y - enemyPosition.y);

	distanceFromPlayerVector.x = deltaX;
	distanceFromPlayerVector.y = deltaY;

	return distanceFromPlayerVector;

}

float PositionStatus::GetDistanceFromPlayer(Vector2 playerPosition, Vector2 enemyPosition)
{
	float distanceX = pow(playerPosition.x - enemyPosition.x, 2);
	float distanceY = pow(playerPosition.y - enemyPosition.y, 2);

	distanceFromPlayer = sqrt(distanceX + distanceY);

	return distanceFromPlayer;
}
