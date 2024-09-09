#ifndef PE_CAMERA_COMPONENT_H
#define PE_CAMERA_COMPONENT_H

#include "SceneComponent.h"
#include "Camera.h"

class CCameraComponent : public CSceneComponent {
private:
    CCamera *Camera;
public:
    CCameraComponent();
    ~CCameraComponent() override;

    CCamera *GetCamera();
    void SetCamera(CCamera *NewCamera);
};

#endif