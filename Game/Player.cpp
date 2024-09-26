#include "Player.h"
#include "MeshFactory.h"
#include "BaseMaterial.h"
#include "MainLevel.h"


CFDPlayer::CFDPlayer()
{
    Controller = new CPlayerController();

    SceneComponent = new CSceneComponent();

    MainCameraComponent = new CCameraComponent();
    MainCamera = new CCamera();
    MainCamera->SetFarPlane(600.0f);
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

void CFDPlayer::Tick(float DeltaTime)
{
    CActor::Tick(DeltaTime);

}

CFDPlayer::~CFDPlayer()
{
    delete MainCamera;
}