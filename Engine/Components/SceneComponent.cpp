#include "SceneComponent.hpp"
#include "CameraComponent.hpp"
#include "PlayerController.hpp"

CSceneComponent::CSceneComponent()
{
    Parent = nullptr;
    SceneComponents = new CArray<CSceneComponent *>();
}

void CSceneComponent::Draw()
{
    if(SceneComponents) {
        glm::mat4 NewTransformMatrix = glm::mat4(1.0f);
        if(CSceneComponent *Parent = GetParent()) {
            NewTransformMatrix = Parent->GetWorldTransform() * GetLocalTransform().GetTransformMatrix();
        } else {
            NewTransformMatrix = GetLocalTransform().GetTransformMatrix();
        }
        SetWorldTransform(NewTransformMatrix);

        for(int32_t I = 0; I < SceneComponents->Num(); ++I) {
            CSceneComponent *SceneComponent = SceneComponents->Get(I);
            if(SceneComponent) {
                SceneComponent->Draw();
            }
        }
    }
}

CSceneComponent::~CSceneComponent()
{
    if(SceneComponents) {
        for(int32_t I = 0; I < SceneComponents->Num(); ++I) {
            CSceneComponent *SceneComponent = SceneComponents->Get(I);
            if(SceneComponent) {
                delete SceneComponent;
            }
        }
        delete SceneComponents;
    }
}

CSceneComponent *CSceneComponent::GetParent()
{
    return Parent;
}

void CSceneComponent::SetParent(CSceneComponent *NewParent)
{
    Parent = NewParent;
}

glm::mat4 CSceneComponent::GetWorldTransform()
{
    return WorldTransform;
}

glm::mat4 *CSceneComponent::GetWorldTransformRef()
{
    return &WorldTransform;
}

void CSceneComponent::SetWorldTransform(glm::mat4 NewTransform)
{
    WorldTransform = NewTransform;
}

CTransform CSceneComponent::GetLocalTransform()
{
    return LocalTransform;
}

CTransform *CSceneComponent::GetLocalTransformRef()
{
    return &LocalTransform;
}

void CSceneComponent::SetLocalTransform(CTransform NewTransform)
{
    LocalTransform = NewTransform;
}

void CSceneComponent::AddComponent(CSceneComponent *SceneComponent)
{
    if(SceneComponents && SceneComponent) {
        glm::mat4 NewTransformMatrix = GetWorldTransform() * SceneComponent->GetLocalTransform().GetTransformMatrix();
        SceneComponent->SetWorldTransform(NewTransformMatrix);
        SceneComponent->SetParent(this);
        SceneComponents->Add(SceneComponent);
    }
}

CSceneComponent *CSceneComponent::RemoveComponent(int32_t Index)
{
    CSceneComponent *SceneComponent = nullptr;
    if(SceneComponents) {
        SceneComponent = SceneComponents->Get(Index);
        SceneComponents->Remove(Index);
    }
    return nullptr;
}

void CSceneComponent::RegisterComponents(CActor *NewOwner)
{
    Owner = NewOwner;
    if(SceneComponents) {
        for(int32_t I = 0; I < SceneComponents->Num(); ++I) {
            CSceneComponent *SceneComponent = SceneComponents->Get(I);
            if(SceneComponent) {
                SceneComponent->RegisterComponents(NewOwner);
            }
        }
    }

    if(CCameraComponent *CameraComponent = Cast<CCameraComponent*>(this)) {
        if(CActor *Owner = GetOwner()) {
            if(CPlayerController *Controller = Cast<CPlayerController *>(Owner->GetController())) {
                Controller->SetCameraComponent(CameraComponent);
            }
        }
    }
}