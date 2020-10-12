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


