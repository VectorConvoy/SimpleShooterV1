#include "SteeringBehaviors.h"

SteeringBehavior::SteeringBehavior()
{
}

SteeringBehavior::~SteeringBehavior()
{
}

Vector2 SteeringBehavior::Seek(Vector2 entityPos, Vector2 targetPos)
{
    Vector2 desiredVelocity = ((Vector2) targetPos - entityPos).Normalized();
    return desiredVelocity;
}

Vector2 SteeringBehavior::Flee(Vector2 entityPos, Vector2 targetPos, float panicDistance)
{
    float panicDistanceSquared = pow(panicDistance, 2);
    Vector2 distanceSq = DistanceSquared(entityPos, targetPos);

    if (distanceSq.Magnitude() > panicDistanceSquared)
    {
        return Vector2(0, 0);
    }
    else
    {
        Vector2 desiredVelocity = ((Vector2)entityPos - targetPos).Normalized();

        return(desiredVelocity);
    }
}

Vector2 SteeringBehavior::Wander(Vector2 entityPos, Vector2 targetPos)
{
    double patrolJitter = 1;
    double patrolRadius = 1;
    double patrolDistance = 2;

    Vector2 circleCenter = entityPos.Normalized() * patrolDistance;
    Vector2 displacement = Vector2(RandomClamped(1, -1) * patrolJitter, RandomClamped(1, -1) * patrolJitter) * patrolRadius;

    return circleCenter + displacement.Normalized();
}



