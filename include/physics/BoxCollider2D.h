#pragma once
#include <box2d/box2d.h>

class BoxCollider2D
{
public:
    class BoxCollider2D(class Quad* InQuad);
    void Update();
private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* fixture;

friend class RigidBody2D;
};
