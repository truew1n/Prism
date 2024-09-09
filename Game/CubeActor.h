#ifndef CFD_CUBE_ACTOR_H
#define CFD_CUBE_ACTOR_H

#include "Actor.h"
#include "MeshComponent.h"
#include "CameraComponent.h"

class CFDCubeActor : public CActor {
public:
    CFDCubeActor();
    void Tick(float DeltaTime) override;
    ~CFDCubeActor() override;

    CSceneComponent *SceneComponent;

    CCameraComponent *MainCameraComponent;
    CCamera *MainCamera;
};

#endif