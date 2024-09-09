#ifndef PE_LEVEL_H
#define PE_LEVEL_H

#include "Actor.h"
#include "Array.h"
#include "PlayerController.h"

class CLevel {
private:
    CPlayerController *PlayerController;
    CArray<CActor *> *Actors;
public:
    CLevel();
    virtual void Tick(float DeltaTime);
    void Draw();
    virtual ~CLevel();

    void AddActor(CActor *NewActor);
    CActor *GetActor(int32_t Index);

    CPlayerController *GetPlayerController();
    void SetPlayerController(CPlayerController *NewPlayerController);
};

#endif