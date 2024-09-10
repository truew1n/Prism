#ifndef CFD_PLAYER_H
#define CFD_PLAYER_H

#include "Actor.h"
#include "MeshComponent.h"
#include "CameraComponent.h"

class CFDPlayer : public CActor {
public:
    CFDPlayer();
    void Tick(float DeltaTime) override;
    ~CFDPlayer() override;

    CSceneComponent *SceneComponent;

    CCameraComponent *MainCameraComponent;
    CCamera *MainCamera;
};

#endif