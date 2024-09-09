#ifndef PE_PLAYER_CONTROLLER_H
#define PE_PLAYER_CONTROLLER_H

#include "Controller.h"
#include "CameraComponent.h"

class CPlayerController : public CController {
private:
    CCameraComponent *CameraComponent;
    CActor *ControlledActor;

public:
    CPlayerController();
    CPlayerController(CActor *Actor);
    virtual void Tick(float DeltaTime) override;
    ~CPlayerController();

    void Possess(CActor *Actor);

    CCameraComponent *GetCameraComponent();
    void SetCameraComponent(CCameraComponent *NewCameraComponent);
};

#endif