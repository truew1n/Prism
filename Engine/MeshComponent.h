#ifndef PE_MESH_COMPONENT_H
#define PE_MESH_COMPONENT_H

#include "SceneComponent.h"
#include "Mesh.h"

class CCameraComponent;

class CMeshComponent : public CSceneComponent {
private:
    CMesh *MMesh;
    CCameraComponent *MCachedCameraComponent;
public:
    CMeshComponent();
    void Tick(float DeltaTime) override;
    void Draw() override;
    ~CMeshComponent() override;

    CMesh *GetMesh();
    void SetMesh(CMesh *Mesh);
};

#endif