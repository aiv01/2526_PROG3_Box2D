#pragma once
#include <box2d/box2d.h>
#include <glm/glm.hpp>

class Physics2D
{
public:
    Physics2D(glm::vec2 InGravity, float InFixedDeltaTime);
    void Step();
    b2Body* CreateBody(const b2BodyDef* InDef);

private:
    b2World World;
    float FixedDeltaTime;
};


