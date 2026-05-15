#pragma once
#include <box2d/box2d.h>

class RigidBody2D
{
public:
    RigidBody2D(class Quad* InQuad);
    void Update();
private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* fixture;
};
