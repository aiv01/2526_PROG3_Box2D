#pragma once
#include <box2d/box2d.h>
#include <functional>

class Quad;
class BoxCollider2D;
/*
struct CollisionCallback
{   
    std::function<void(Quad*)> OnEnter = [](Quad* Obj) { };
    Quad* Object = nullptr;
};
*/
struct CollisionPair//to save entering collisions here
{
    BoxCollider2D* A = nullptr;
    BoxCollider2D* B = nullptr;
};

class PhysicsContactListener: public b2ContactListener
{
public:
    void BeginContact(b2Contact* InContact);
    void EndContact(b2Contact* InContact);
    void StayContact();

private:
    std::vector<CollisionPair> ActiveCollisions;//without list not able to manager more then one staying collision i think
};