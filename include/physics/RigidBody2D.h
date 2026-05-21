#pragma once
#include <box2d/box2d.h>
#include <glm/glm.hpp>

enum RBodyType
{
    Static =  b2BodyType::b2_staticBody,
    Kinematic = b2BodyType::b2_kinematicBody,
    Dynamic = b2BodyType::b2_dynamicBody
};

class RigidBody2D
{
public:
    RigidBody2D(class Quad* InQuad, RBodyType InBodyType);
    void Update();
    void AddForce(glm::vec2 InForce);
    void AddImpulse(glm::vec2 InForce);
    void SetVelocity(glm::vec2 InVelocity);
private:
    class Quad* Object;
    class b2Body* Body;
    class b2Fixture* fixture;

friend class BoxCollider2D;
};
