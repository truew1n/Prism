#ifndef CFD_SPHERE_ACTOR_H
#define CFD_SPHERE_ACTOR_H

#include "Actor.h"
#include "MeshComponent.h"
#include "AssetLoader.h"

class CFDSphereActor : public CActor {
public:
    CFDSphereActor();
    void Tick(float DeltaTime) override;
    ~CFDSphereActor();

    CSceneComponent *Root;

    CMeshComponent *SphereComponent;
    CMaterial *SphereMaterial;
    CMesh *SphereMesh;

    CMeshComponent *TerrainComponent;
    CMaterial *TerrainMaterial;
    CMesh *TerrainMesh;

    CAsset *YuccaAsset;
    CAsset *ZilAsset;
};

#endif