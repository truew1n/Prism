#include "Level.hpp"

CLevel::CLevel()
{
    PlayerController = nullptr;
    Actors = new CArray<CActor *>();
}

void CLevel::Tick(float DeltaTime)
{
    for(int32_t I = 0; I < Actors->Num(); ++I) {
        Actors->Get(I)->Tick(DeltaTime);
    }
}

void CLevel::Draw()
{
    for(int32_t I = 0; I < Actors->Num(); ++I) {
        Actors->Get(I)->Draw();
    }
}

CLevel::~CLevel()
{
    CActor *Actor;
    for(int32_t I = 0; I < Actors->Num(); ++I) {
        Actor = Actors->Get(I);
        if(Actor) {
            delete Actor;
        }
    }
}

void CLevel::AddActor(CActor *NewActor)
{
    if(NewActor) {
        NewActor->SetLevel(this);
        Actors->Add(NewActor);
    }
}

CActor *CLevel::GetActor(int32_t Index)
{
    if(Actors->InBounds(Index)) {
        return Actors->Get(Index);
    }

    return nullptr;
}

CPlayerController *CLevel::GetPlayerController()
{
    return PlayerController;
}

void CLevel::SetPlayerController(CPlayerController *NewPlayerController)
{
    if(NewPlayerController) {
        PlayerController = NewPlayerController;
    }
}