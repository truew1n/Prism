#ifndef PE_CAMERA_COMPONENT_HPP
#define PE_CAMERA_COMPONENT_HPP

#include "SceneComponent.hpp"
#include "Camera.hpp"

class CCameraComponent : public CSceneComponent {
private:
    CCamera *Camera;
public:
    CCameraComponent();
    void Tick(float DeltaTime) override;
    ~CCameraComponent();
    
    CCamera *GetCamera();
    void SetCamera(CCamera *NewCamera);
};

#endif