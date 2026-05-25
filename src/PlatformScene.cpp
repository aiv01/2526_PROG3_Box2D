#include "PlatformScene.h"
#include "OGLQuadRenderer.h"
#include "OrthoCamera.h"
#include "physics/RigidBody2D.h"
#include "physics/BoxCollider2D.h"
#include <iostream>

void PlatformScene::Start() 
{
    Camera = new OrthoCamera(Win.GetWidth(), Win.GetHeight(), 10.f);

    Quad* Floor = new Quad(Camera->GetOrthoWidth(), 1);
    Floor->Position = glm::vec3{0, -Camera->GetOrthoHeight() * 0.5f + Floor->Scale.y * 0.5f, 0};
    
    CollisionCallback FloorCb;
    Floor->BoxCollider = new BoxCollider2D(Floor, FloorCb);
    Floor->Name = "Floor";

    Player = new Quad(1, 1);
    Player->Position = glm::vec3{0, 0, 0};
    Player->Color = Color_Red;
    Player->RigidBody = new RigidBody2D(Player, RBodyType::Dynamic);

    CollisionCallback PlayerCb;
    PlayerCb.OnEnter = [](Quad* Object) {
        std::cout << "Player OnEnter: " << Object->Name << "\n";
    };
    Player->BoxCollider = new BoxCollider2D(Player, PlayerCb);
    // TODO: Improve callback implemtation like:
    // Player->BoxCollider->OnEnter = function;

    Platform = new Quad(3, 1);
    Platform->Position = glm::vec3(3, 0, 0);
    Platform->Color = Color_Yellow;
    Platform->RigidBody = new RigidBody2D(Platform, RBodyType::Kinematic);

    // TODO: Avoid to define callback for the one who dont need it.
    CollisionCallback PlatformCb;
    Platform->BoxCollider = new BoxCollider2D(Platform, PlatformCb);

    Quads.push_back(Floor);
    Quads.push_back(Player);
    Quads.push_back(Platform);
    
    SelectedMoveForce = {0, 0};
    SelectedJumpForce = {0, 0};
}

void PlatformScene::Update()
{
    Renderer.Draw(Quads, Camera);
    
    float MoveForce = 6.f;
    float JumpForce = 5.f;
    
    // Move
    if (Win.IsKeyPressed(Key::KEY_LEFT)) 
    {
        SelectedMoveForce = {-MoveForce, 0};
    }
    else if (Win.IsKeyPressed(Key::KEY_RIGHT)) 
    {
        SelectedMoveForce = {MoveForce, 0};
    }

    //Jump
    static bool JumpPressed = false;
    if (!JumpPressed && Win.IsKeyPressed(Key::KEY_UP)) 
    {
        JumpPressed = true;
        SelectedJumpForce = {0, JumpForce};
    } 
    else 
    {
        JumpPressed = Win.IsKeyPressed(Key::KEY_UP);
    }

    //Platform
    //TODO: Make platform move left-right 
    float Speed = 1.f;
    glm::vec2 PlatDir = {-1, 0};
    Platform->RigidBody->SetVelocity(PlatDir * Speed);
}

void PlatformScene::FixedUpdate()
{
    for (auto* Each : Quads) 
    {
        if (Each->RigidBody)
            Each->RigidBody->Update();
    }

    Player->RigidBody->AddForce(SelectedMoveForce);
    SelectedMoveForce = {0, 0};

    Player->RigidBody->AddImpulse(SelectedJumpForce);
    SelectedJumpForce = {0, 0};
}

void PlatformScene::Destroy()
{
    delete Camera;
    for (auto* Each : Quads) delete Each;
}
