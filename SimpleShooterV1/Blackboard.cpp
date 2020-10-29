#include "Blackboard.h"

void Blackboard::SetMoveDirection(Vector2 dest)
{
    moveDirection = dest;
}

Vector2 Blackboard::GetMoveDirection()
{
    return moveDirection;
}

Blackboard::Blackboard()
{
}

Blackboard::~Blackboard()
{
}

void Blackboard::SetEnemy(Enemy* enemy)
{
    AIOwner = enemy;
}

Enemy* Blackboard::GetEnemy()
{
    return AIOwner;
}

void Blackboard::SetPlayer(Player* thePlayer)
{
    this->player = thePlayer;
}

Player* Blackboard::GetPlayer()
{
    return this->player;
}

void Blackboard::SetPlayerPos(Vector2 pos)
{
    //Unsure if needed
}

Vector2 Blackboard::GetPlayerPos()
{
    return Vector2();
}
