#include "MainLevel.h"
#include "Player.h"

#include "MeshFactory.h"
#include "BaseMaterial.h"

CFDMainLevel::CFDMainLevel()
{
    LastX = 0.0;
    LastY = 0.0;

    StartScale = glm::vec3(1.0f);
    MaxTotalScale = 3.141592 * 2.0f;
    ScaleStep = 1.0f;
    TotalScale = 0.0f;
    
    TestActor = new CActor();
    CMeshComponent *MeshComponent = new CMeshComponent();
    CMesh *CubeMesh = CMeshFactory::GenerateCube(2.0f);
    CubeMesh->SetMaterial(new CFDBaseMaterial());
    MeshComponent->SetMesh(CubeMesh);
    TestActor->RootComponent = MeshComponent;

    MeshComponent->GetLocalTransformRef()->SetScale(StartScale);

    TestActor->RootComponent->RegisterComponents(TestActor);

    Player = new CFDPlayer();

    AddActor(Player);
    AddActor(TestActor);

    SetPlayerController(Cast<CPlayerController *>(Player->GetController()));
}

void CFDMainLevel::Tick(float DeltaTime)
{
    CLevel::Tick(DeltaTime);

    CTransform *TestTransform = TestActor->GetTransformRef();
    
    TestTransform->SetScale(
        glm::vec3(
            StartScale.x + (sin(TotalScale) + 1) / 2.0f,
            StartScale.y + (cos(TotalScale) + 1) / 2.0f,
            StartScale.z + (cos(TotalScale) + 1) / 2.0f
        )
    );
    
    TotalScale = fmodf(TotalScale + ScaleStep * DeltaTime, MaxTotalScale);
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

                if (Camera->GetPitch() > 89.9f)
                    Camera->SetPitch(89.9f);
                if (Camera->GetPitch() < -89.9f)
                    Camera->SetPitch(-89.9f);
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