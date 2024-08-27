#include "ActorComponent.hpp"

CActorComponent::CActorComponent()
{
    Owner = nullptr;
}

void CActorComponent::Tick(float DeltaTime)
{
    CObject::Tick(DeltaTime);
    
}

CActorComponent::~CActorComponent()
{
    
}

CActor *CActorComponent::GetOwner()
{
    return Owner;
}

void CActorComponent::SetOwner(CActor *NewOwner)
{
    Owner = NewOwner;
}