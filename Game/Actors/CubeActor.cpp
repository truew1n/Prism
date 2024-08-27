#include "CubeActor.hpp"
#include "MeshFactory.hpp"
#include "BaseMaterial.hpp"
#include "MainLevel.hpp"


CFDCubeActor::CFDCubeActor()
{
    Controller = new CPlayerController();
    
    SceneComponent = new CSceneComponent();

    CubeMeshComponent = new CMeshComponent();
    CubeMesh = CMeshFactory::GenerateCube(2.0f);
    CubeMaterial = new CFDBaseMaterial();
    CubeMesh->SetMaterial(CubeMaterial);
    CubeMeshComponent->SetMesh(CubeMesh);
    CubeMeshComponent->SetLocalTransform(
        CTransform(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        )
    );

    MainCameraComponent = new CCameraComponent();
    MainCamera = new CCamera();
    MainCameraComponent->SetCamera(MainCamera);
    MainCameraComponent->SetLocalTransform(
        CTransform(
            glm::vec3(0.0f, 0.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        )
    );

    RootComponent = SceneComponent;
    SceneComponent->AddComponent(CubeMeshComponent);
    SceneComponent->AddComponent(MainCameraComponent);

    RootComponent->RegisterComponents(this);
}

void CFDCubeActor::Tick(float DeltaTime)
{
    CActor::Tick(DeltaTime);
    
    CTransform *Transform = SceneComponent->GetLocalTransformRef();
    Transform->RotateX(30.0f * DeltaTime);
}

CFDCubeActor::~CFDCubeActor()
{
    delete CubeMesh;
    delete CubeMaterial;
    delete MainCamera;
}