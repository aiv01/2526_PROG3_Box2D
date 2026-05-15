#include "physics/RigidBody2D.h"
#include "ServiceRegistry.h"
#include "Quad.h"

RigidBody2D::RigidBody2D(Quad* InQuad)
{
    Object = InQuad;

    //1. Create Body in the Physics World
    b2BodyDef BodyDef;
    BodyDef.type = b2_dynamicBody;
    BodyDef.position = b2Vec2{Object->Position.x, Object->Position.y};

    auto* Physics = ServiceRegistry::GetInstance().GetPhysics();
    Body = Physics->CreateBody(&BodyDef);

    //2. At least one fixture per RigidBody
    glm::vec3 bSize = InQuad->Scale;
    bSize *= 0.5f; //extent like

    b2PolygonShape box;
    box.SetAsBox(bSize.x, bSize.y);  //not really significative for rigid body (without collision). Just need to be > 0

    b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 1.f;      //Kg/m2  for dynamic body must be > 0.f
    fixtureDef.isSensor = false;
                          
    fixtureDef.filter.categoryBits = 0;   //No collision detect  (see default in b2filter constructor)
    fixtureDef.filter.maskBits = 0;       //No collision detect  (see default in b2filter constructor)

    fixture = Body->CreateFixture(&fixtureDef);
}

void RigidBody2D::Update() 
{
    b2Vec2 B2Pos = Body->GetPosition();
    Object->Position.x = B2Pos.x;
    Object->Position.y = B2Pos.y;
}
