#include "MainLevel.hpp"
#include "CubeActor.hpp"
#include "SphereActor.hpp"

CFDMainLevel::CFDMainLevel()
{
    LastX = 0.0f;
    LastY = 0.0f;

    CubeActor = new CFDCubeActor();
    SphereActor = new CFDSphereActor();
    
    AddActor(CubeActor);
    AddActor(SphereActor);

    SetPlayerController(Cast<CPlayerController *>(CubeActor->GetController()));
}

void CFDMainLevel::Tick(float DeltaTime)
{
    CLevel::Tick(DeltaTime);
    
}

CFDMainLevel::~CFDMainLevel()
{

}

void CFDMainLevel::MouseCallback(double X, double Y)
{
    float XOffset = X - LastX;
    float YOffset = LastY - Y;

    LastX = X;
    LastY = Y;

    float Sensitivity = 0.1f;
    XOffset *= Sensitivity;
    YOffset *= Sensitivity;

    if (CPlayerController *PlayerController = GetPlayerController()) {
        if (CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
            if (CCamera *Camera = CameraComponent->GetCamera()) {
                Camera->SetYaw(Camera->GetYaw() + XOffset);
                Camera->SetPitch(Camera->GetPitch() + YOffset);

                if (Camera->GetPitch() > 89.0f)
                    Camera->SetPitch(89.0f);
                if (Camera->GetPitch() < -89.0f)
                    Camera->SetPitch(-89.0f);
            }
        }
    }
}

void CFDMainLevel::ResizeCallback(int32_t Width, int32_t Height)
{
    if (CPlayerController *PlayerController = GetPlayerController()) {
        if (CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
            if (CCamera *Camera = CameraComponent->GetCamera()) {
                float AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
                Camera->SetAspectRatio(AspectRatio);
            }
        }
    }
}