#pragma once
#include <box2d/box2d.h>
#include <physics/PhysicsContactListener.h>

class BoxCollider2D
{
public:
    class BoxCollider2D(class Quad* InQuad, CollisionCallback InCallback);
    void Update();
private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* fixture;
    CollisionCallback UserData;

friend class RigidBody2D;
};
