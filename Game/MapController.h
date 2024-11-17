#ifndef G_PERLIN_GRID_H
#define G_PERLIN_GRID_H

#include "Actor.h"
#include "MeshComponent.h"

class CAsset;

class GMapController : public CActor {
public:
    GMapController();
    virtual void Draw() override;
    void Tick(float DeltaTime) override;
    ~GMapController() override;

    CArray<CMeshComponent *> OpaqueObjects;
    CArray<CMeshComponent *> TransparentObjects;

    CCameraComponent *CachedCameraComponent;

    CAsset *YuccaAsset;
};

#endif