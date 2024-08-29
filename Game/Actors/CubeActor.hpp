#ifndef CFD_CUBE_ACTOR_HPP
#define CFD_CUBE_ACTOR_HPP

#include "Actor.hpp"
#include "MeshComponent.hpp"
#include "CameraComponent.hpp"

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