#ifndef PE_MESH_COMPONENT_HPP
#define PE_MESH_COMPONENT_HPP

#include "SceneComponent.hpp"
#include "Mesh.hpp"

class CMeshComponent : public CSceneComponent {
private:
    CMesh *Mesh;
public:
    CMeshComponent();
    void Draw(CTransform RootTransform) override;
    ~CMeshComponent();

    CMesh *GetMesh();
    void SetMesh(CMesh *Mesh);
};

#endif