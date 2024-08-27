#include "CameraComponent.hpp"

CCameraComponent::CCameraComponent()
{
    Camera = nullptr;
}

void CCameraComponent::Tick(float DeltaTime)
{
    
}

CCameraComponent::~CCameraComponent()
{
    if(Camera) {
        delete Camera;
    }
}

CCamera *CCameraComponent::GetCamera()
{
    return Camera;
}

void CCameraComponent::SetCamera(CCamera *NewCamera)
{
    Camera = NewCamera;
}