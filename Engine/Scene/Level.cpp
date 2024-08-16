#include "Level.hpp"

CLevel::CLevel()
{
    Actors = new CArray<CActor *>();
}

void CLevel::Tick(float DeltaTime)
{
    for(int32_t I = 0; I < Actors->Num(); ++I) {
        Actors->Get(I)->Tick(DeltaTime);
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