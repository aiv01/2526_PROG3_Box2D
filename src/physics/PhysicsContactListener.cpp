#include "physics/PhysicsContactListener.h"
#include "physics/BoxCollider2D.h"
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

    auto* ColliderA = reinterpret_cast<BoxCollider2D*>(FixtA.pointer);
    auto* ColliderB = reinterpret_cast<BoxCollider2D*>(FixtB.pointer);

    Quad* ObjectA = ColliderA->GetObject();
    Quad* ObjectB = ColliderB->GetObject();

    ActiveCollisions.push_back({ ColliderA, ColliderB });

    if (ColliderA->OnEnter)
    {
        ColliderA->OnEnter(ObjectB);
    }

    if (ColliderB->OnEnter)
    {
        ColliderB->OnEnter(ObjectA);
    }
}


void PhysicsContactListener::EndContact(b2Contact* InContact) 
{
    std::cout << "EndContact\n";

    auto& FixtA = InContact->GetFixtureA()->GetUserData();
    auto& FixtB = InContact->GetFixtureB()->GetUserData();

    if (FixtA.pointer == 0 || FixtB.pointer == 0)
    {
        return;
    }

    auto* ColliderA = reinterpret_cast<BoxCollider2D*>(FixtA.pointer);
    auto* ColliderB = reinterpret_cast<BoxCollider2D*>(FixtB.pointer);

    Quad* ObjectA = ColliderA->GetObject();
    Quad* ObjectB = ColliderB->GetObject();

    //search and erase the pair 
    for (int i = 0; i < ActiveCollisions.size(); i++)
    {
        CollisionPair Pair = ActiveCollisions[i];

        bool SameOrder = Pair.A == ColliderA && Pair.B == ColliderB;
        bool InvertedOrder = Pair.A == ColliderB && Pair.B == ColliderA;
        if (SameOrder || InvertedOrder)
        {
            ActiveCollisions.erase(ActiveCollisions.begin() + i);
            break;
        }
    }

    if (ColliderA->OnExit)
    {
        ColliderA->OnExit(ObjectB);
    }

    if (ColliderB->OnExit)
    {
        ColliderB->OnExit(ObjectA);
    }
}


void PhysicsContactListener::StayContact()
{
    for (const CollisionPair& Pair : ActiveCollisions)
    {

        Quad* ObjectA = Pair.A->GetObject();
        Quad* ObjectB = Pair.B->GetObject();

        if (Pair.A->OnStay)
        {
            Pair.A->OnStay(ObjectB);
        }

        if (Pair.B->OnStay)
        {
            Pair.B->OnStay(ObjectA);
        }
    }
}