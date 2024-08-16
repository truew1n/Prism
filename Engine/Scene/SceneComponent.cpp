#include "SceneComponent.hpp"


CSceneComponent::CSceneComponent()
{

}

void CSceneComponent::Draw(CTransform RootTransform)
{
    CTransform NewTransform = RootTransform + GetTransform();
    for(int32_t I = 0; I < Compontents->Num(); ++I) {
        Compontents->Get(I)->Draw(NewTransform);
    }
}

CSceneComponent::~CSceneComponent()
{
    for(int32_t I = 0; I < Compontents->Num(); ++I) {
        delete Compontents->Get(I);
    }
}

CTransform CSceneComponent::GetTransform()
{
    return Transform;
}

void CSceneComponent::SetTransform(CTransform NewTransform)
{
    Transform = NewTransform;
}