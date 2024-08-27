#include "PlayerController.hpp"


CPlayerController::CPlayerController()
{
    CameraComponent = nullptr;
    ControlledActor = nullptr;
}

CPlayerController::CPlayerController(CActor *Actor)
{
    CameraComponent = nullptr;
    ControlledActor = Actor;
}

void CPlayerController::Tick(float DeltaTime)
{
    CController::Tick(DeltaTime);


}

CPlayerController::~CPlayerController()
{
    
}

void CPlayerController::Possess(CActor *Actor)
{
    if(Actor) {
        ControlledActor = Actor;
        ControlledActor->SetController(this);
    }
}

CCameraComponent *CPlayerController::GetCameraComponent()
{
    return CameraComponent;
}

void CPlayerController::SetCameraComponent(CCameraComponent *NewCameraComponent)
{
    CameraComponent = NewCameraComponent;
}