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

    CAsset *YuccaAsset;
    CAsset *TerrainAsset;
    CAsset *ZilAsset;
};

#endif