#include "Player.h"
#include "MeshFactory.h"
#include "BaseMaterial.h"
#include "MainLevel.h"


GPlayer::GPlayer()
{
    Controller = new CPlayerController();

    SceneComponent = new CSceneComponent();

    MainCameraComponent = new CCameraComponent();
    MainCamera = new CCamera();
    MainCamera->SetFarPlane(500.0f);
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
    RootComponent->GetLocalTransformRef()->Translate(-385.763, 30.9455, 436.567);
}

void GPlayer::Tick(float DeltaTime)
{
    CActor::Tick(DeltaTime);
    
}

GPlayer::~GPlayer()
{
    delete MainCamera;
}