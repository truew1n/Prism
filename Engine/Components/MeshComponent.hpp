#ifndef PE_MESH_COMPONENT_HPP
#define PE_MESH_COMPONENT_HPP

#include "SceneComponent.hpp"
#include "Mesh.hpp"

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