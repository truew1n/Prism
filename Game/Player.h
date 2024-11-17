#ifndef G_PLAYER_H
#define G_PLAYER_H

#include "Actor.h"
#include "MeshComponent.h"
#include "CameraComponent.h"

class GPlayer : public CActor {
public:
    GPlayer();
    void Tick(float DeltaTime) override;
    ~GPlayer() override;

    CSceneComponent *SceneComponent;

    CCameraComponent *MainCameraComponent;
    CCamera *MainCamera;
};

#endif