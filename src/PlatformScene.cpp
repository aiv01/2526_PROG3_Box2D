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
    
    Floor->Name = "Floor";
    Floor->BoxCollider = new BoxCollider2D(Floor);//i ve integrated the callback function inside boxcollider
    Floor->BoxCollider->OnEnter = [](Quad* Object) {
        std::cout << "Floor OnEnter: " << Object->Name << "\n";
    };
    

    Floor->BoxCollider->OnExit = [](Quad* Object) {
        std::cout << "Floor OnExit: " << Object->Name << "\n";
    };


    Player = new Quad(1, 1);
    Player->Position = glm::vec3{0, 0, 0};
    Player->Color = Color_Red;
    Player->RigidBody = new RigidBody2D(Player, RBodyType::Dynamic);
    Player->Name="Player1";
    Player->BoxCollider = new BoxCollider2D(Player);

    Player->BoxCollider->OnEnter = [](Quad* Object) {
        std::cout << "Player OnEnter: " << Object->Name << "\n";
    };

    Platform = new Quad(3, 1);
    Platform->Position = glm::vec3(3, 0, 0);
    Platform->Color = Color_Yellow;
    Platform->RigidBody = new RigidBody2D(Platform, RBodyType::Kinematic);
    Platform->Name="Platform";
    Platform->BoxCollider = new BoxCollider2D(Platform);
    Platform->BoxCollider->OnStay = [](Quad* Object) {
        std::cout << "Platform OnStay: " << Object->Name << "\n";
    };

    Quad* Player2 = new Quad(1, 1);
    Player2->Position = glm::vec3(3, 2, 0);
    Player2->Color = Color_Purple;
    Player2->RigidBody = new RigidBody2D(Player2, RBodyType::Dynamic);
    Player2->BoxCollider = new BoxCollider2D(Player2);
    Player2->Name = "Player2";

    Quads.push_back(Floor);
    Quads.push_back(Player);
    Quads.push_back(Platform);
    Quads.push_back(Player2);
    
    SelectedMoveForce = {0, 0};
    SelectedJumpForce = {0, 0};
}

void PlatformScene::Update()
{
    Renderer.Draw(Quads, Camera);
    
    float MoveForce = 6.f;
    float JumpForce = 10.f;
    
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
    static float PlatformTime = 0.0f;
    PlatformTime += Win.GetDeltaTime();
    float Speed = 1.f;
    glm::vec2 PlatVel = {std::sin(PlatformTime) * Speed, 0};
    Platform->RigidBody->SetVelocity(PlatVel);
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
