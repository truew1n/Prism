#ifndef PE_PLAYER_CONTROLLER_HPP
#define PE_PLAYER_CONTROLLER_HPP

#include "Controller.hpp"
#include "CameraComponent.hpp"

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