#include "MainLevel.h"
#include "Player.h"
#include "PerlinGrid.h"
#include "MeshFactory.h"
#include "BaseMaterial.h"

CFDMainLevel::CFDMainLevel()
{
    LastX = 0.0;
    LastY = 0.0;

    Player = new CFDPlayer();
    PerlinGrid = new CFDPerlinGrid();

    AddActor(Player);
    AddActor(PerlinGrid);

    SetPlayerController(Cast<CPlayerController *>(Player->GetController()));
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
    float XOffset = (float)(X - LastX);
    float YOffset = (float)(LastY - Y);

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

                if (Camera->GetPitch() > 89.9f) {
                    Camera->SetPitch(89.9f);
                }
                if (Camera->GetPitch() < -89.9f) {
                    Camera->SetPitch(-89.9f);
                }
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