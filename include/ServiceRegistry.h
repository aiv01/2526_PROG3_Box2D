#pragma once

#include "physics/Physics2D.h"

class ServiceRegistry 
{
public:
    static ServiceRegistry& GetInstance()
    {
        static ServiceRegistry Instance{};
        return Instance;
    }

    void SetPhysics(Physics2D* InPhy) {
        Physics = InPhy;
    }

    Physics2D* GetPhysics() 
    {
        return Physics;
    }

private:
    Physics2D* Physics;
};