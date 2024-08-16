#include "Actor.hpp"


CActor::CActor()
{

}

void CActor::Draw()
{
    if(RootComponent) {
        RootComponent->Draw(CTransform());
    }
}

void CActor::Tick(float DeltaTime)
{
    CObject::Tick(DeltaTime);


}

CActor::~CActor()
{
    if(RootComponent) {
        delete RootComponent;
    }
}

CTransform CActor::GetTransform()
{
    if(RootComponent) {
        return RootComponent->GetTransform();
    }

    return CTransform();
}

void CActor::SetTransform(CTransform NewTransform)
{
    if(RootComponent) {
        RootComponent->SetTransform(NewTransform);
    }
}