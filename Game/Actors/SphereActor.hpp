#ifndef CFD_SPHERE_ACTOR_HPP
#define CFD_SPHERE_ACTOR_HPP

#include "Actor.hpp"
#include "MeshComponent.hpp"
#include "AssetLoader.hpp"

class CFDSphereActor : public CActor {
public:
    CFDSphereActor();
    void Tick(float DeltaTime) override;
    ~CFDSphereActor();

    CSceneComponent *Root;

    CMeshComponent *SphereComponent;
    CMesh *SphereMesh;

    CMeshComponent *TerrainComponent;
    CMaterial *TerrainMaterial;
    CMesh *TerrainMesh;

    CAsset *YuccaAsset;
    CAsset *ZilAsset;
};

#endif