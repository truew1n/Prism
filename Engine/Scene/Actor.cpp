#include "Actor.hpp"
#include "Level.hpp"

CActor::CActor()
{
    Level = nullptr;
    Controller = nullptr;
    RootComponent = nullptr;
}

void CActor::Draw()
{
    if(RootComponent) {
        RootComponent->Draw();
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

CLevel *CActor::GetLevel()
{
    return Level;
}

void CActor::SetLevel(CLevel *NewLevel)
{
    if(NewLevel) {
        Level = NewLevel;
    }
}

CTransform CActor::GetTransform()
{
    if(RootComponent) {
        return RootComponent->GetLocalTransform();
    }

    return CTransform();
}

CTransform *CActor::GetTransformRef()
{
    if(RootComponent) {
        return RootComponent->GetLocalTransformRef();
    }

    return nullptr;
}

void CActor::SetTransform(CTransform NewTransform)
{
    if(RootComponent) {
        RootComponent->SetLocalTransform(NewTransform);
    }
}

CController *CActor::GetController()
{
    return Controller;
}

void CActor::SetController(CController *NewController)
{
    Controller = NewController;
}