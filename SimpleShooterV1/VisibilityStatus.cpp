#include "VisibilityStatus.h"

void VisibilityStatus::CheckEnemySight(Vector2 playerPos, Vector2 enemyPos, Enemy::DIRECTION direction)
{

	//TO-DO: Expand so instead of a single x/y value, checks a range of x/y values to accomodate sprite size
	//Currently coded so that only the center of the sprite will be detected
	playerInSight = false;
	if (playerPos.x != enemyPos.x && playerPos.y != enemyPos.y)
	{
		//Player not in sight
		playerInSight = false;
	}
	else
	{
		float deltaX = playerPos.x - enemyPos.x;
		float deltaY = playerPos.y - enemyPos.y;

		float delta = (deltaX == 0 ? deltaY : deltaX);

		if (abs(delta) > sightDistance)
		{
			playerInSight = false;
		}
		else if (direction == Enemy::DIRECTION::up || direction == Enemy::DIRECTION::right)
		{
			if (delta > 0)
			{
				playerInSight = true;
			}
		}
		else if (direction == Enemy::DIRECTION::down || direction == Enemy::DIRECTION::left)
		{
			if (delta < 0)
			{
				playerInSight = true;
			}
		}
	}
}

bool VisibilityStatus::GetPlayerInSight()
{
	return playerInSight;
}
