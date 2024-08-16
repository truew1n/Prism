#include "ActorComponent.hpp"


CActorComponent::CActorComponent()
{

}

CActor *CActorComponent::GetOwner()
{
    return Owner;
}

void CActorComponent::Tick(float DeltaTime)
{
    CObject::Tick(DeltaTime);
    
}

CActorComponent::~CActorComponent()
{
    
}