#include "CameraComponent.hpp"

CCameraComponent::CCameraComponent()
{
    Camera = nullptr;
}

CCameraComponent::~CCameraComponent()
{
    
}

CCamera *CCameraComponent::GetCamera()
{
    return Camera;
}

void CCameraComponent::SetCamera(CCamera *NewCamera)
{
    Camera = NewCamera;
}