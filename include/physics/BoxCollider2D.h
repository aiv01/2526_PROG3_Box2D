#pragma once
#include <box2d/box2d.h>
#include <physics/PhysicsContactListener.h>


class BoxCollider2D
{
public:
    class BoxCollider2D(class Quad* InQuad/*, CollisionCallback InCallback*/);
    void Update();

    std::function<void(Quad*)> OnEnter = nullptr;//they are function, must be public or have caller and setter?
    std::function<void(Quad*)> OnExit = nullptr;

    std::function<void(Quad*)> OnStay = nullptr;
    class Quad* GetObject() const;

private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* fixture;
    /*CollisionCallback UserData;*/

friend class RigidBody2D;
};
