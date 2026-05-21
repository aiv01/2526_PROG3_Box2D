#include "physics/PhysicsContactListener.h"
#include <iostream>

void PhysicsContactListener::BeginContact(b2Contact* InContact) 
{
    std::cout << "BeginContact\n";

    auto& FixtA = InContact->GetFixtureA()->GetUserData();
    auto& FixtB = InContact->GetFixtureB()->GetUserData();

    if (FixtA.pointer == 0 || FixtB.pointer == 0)
    {
        return;
    }

    auto* CbA = reinterpret_cast<CollisionCallback*>(FixtA.pointer);
    auto* CbB = reinterpret_cast<CollisionCallback*>(FixtB.pointer);

    CbA->OnEnter(CbB->Object);
    CbB->OnEnter(CbA->Object);
}

void PhysicsContactListener::EndContact(b2Contact* InContact) 
{
    std::cout << "EndContact\n";
}