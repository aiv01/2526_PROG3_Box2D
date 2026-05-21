#include "physics/Physics2D.h"

Physics2D::Physics2D(glm::vec2 InGravity, float InFixedDeltaTime)
    : World(b2Vec2{InGravity.x, InGravity.y})
{
    FixedDeltaTime = InFixedDeltaTime;
    World.SetContactListener(&Listener);
}

void Physics2D::Step() {
    World.Step(FixedDeltaTime, 8, 3);
}

b2Body* Physics2D::CreateBody(const b2BodyDef* InDef)
{
    return World.CreateBody(InDef);
}
