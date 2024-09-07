#include "CubeActor.hpp"
#include "MeshFactory.hpp"
#include "BaseMaterial.hpp"
#include "MainLevel.hpp"


CFDCubeActor::CFDCubeActor()
{
    Controller = new CPlayerController();
    
    SceneComponent = new CSceneComponent();

    MainCameraComponent = new CCameraComponent();
    MainCamera = new CCamera();
    MainCamera->SetFarPlane(200.0f);
    MainCameraComponent->SetCamera(MainCamera);
    MainCameraComponent->SetLocalTransform(
        CTransform(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        )
    );

    RootComponent = SceneComponent;
    SceneComponent->AddComponent(MainCameraComponent);

    RootComponent->RegisterComponents(this);
}

void CFDCubeActor::Tick(float DeltaTime)
{
    CActor::Tick(DeltaTime);
    
    // CTransform *Transform = SceneComponent->GetLocalTransformRef();
    // Transform->RotateX(30.0f * DeltaTime);
}

CFDCubeActor::~CFDCubeActor()
{
    delete MainCamera;
}