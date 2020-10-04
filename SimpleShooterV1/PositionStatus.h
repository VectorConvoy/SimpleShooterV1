#pragma once
#include "MathHelper.h"
#define _POSITIONSTATUS_H

class PositionStatus
{
public:
	bool GetCloseToPlayer() { return closeToPlayer; }
	float GetDistanceFromPlayer() { return distanceFromPlayer; };
	float GetDistanceFromPlayer(Vector2 playerPosition, Vector2 enemyPosition);

	Vector2 GetVectorDistanceFromPlayer() { return distanceFromPlayerVector; }
	Vector2 GetVectorDistanceFromPlayer(Vector2 playerPosition, Vector2 enemyPosition);

	void SetCloseToPlayer(float minDeltaDistance = 50.0f);
	
private:
	bool closeToPlayer;
	float distanceFromPlayer;
	Vector2 distanceFromPlayerVector;
};