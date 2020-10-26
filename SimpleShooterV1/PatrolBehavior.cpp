#include "PatrolBehavior.h"


Vector2 PatrolBehavior::Wander(Vector2 entityPos, Vector2 targetPos)
{
    Vector2 wanderTarget = targetPos + Vector2(RandomClamped(1, -1) * patrolJitter, RandomClamped(1, -1) * patrolJitter);
    wanderTarget = wanderTarget.Normalized();


    //Scale with circle radius
    wanderTarget = wanderTarget * patrolRadius;


    Vector2 circleCenter = entityPos.Normalized() * patrolDistance;
    Vector2 displacement = Vector2(0, -1) * patrolRadius;

    displacement.x *= patrolJitter;
    displacement.y *= patrolJitter;


    return circleCenter + displacement;
}
