#ifndef PE_LEVEL_HPP
#define PE_LEVEL_HPP

#include "Actor.hpp"
#include "Array.hpp"
#include "PlayerController.hpp"

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