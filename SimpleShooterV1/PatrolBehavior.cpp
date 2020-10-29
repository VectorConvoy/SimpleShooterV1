#include "PatrolBehavior.h"


Vector2 PatrolBehavior::Wander(Vector2 entityPos, Vector2 targetPos)
{
    Vector2 wanderTarget = targetPos + Vector2((float) (RandomClamped(1, -1) * patrolJitter), (float) (RandomClamped(1, -1) * patrolJitter));
    wanderTarget = wanderTarget.Normalized();


    //Scale with circle radius
    wanderTarget = wanderTarget * (float) patrolRadius;


    Vector2 circleCenter = entityPos.Normalized() * (float) patrolDistance;
    Vector2 displacement = Vector2(0, -1) * (float) patrolRadius;

    displacement.x *= (float) patrolJitter;
    displacement.y *= (float) patrolJitter;


    return circleCenter + displacement;
}
