#ifndef CFD_PERLIN_GRID_H
#define CFD_PERLIN_GRID_H

#include "Actor.h"
#include "MeshComponent.h"

class CFDGrassMaterial;

class CFDPerlinGrid: public CActor {
public:
    CFDPerlinGrid();
    void Tick(float DeltaTime) override;
    ~CFDPerlinGrid() override;

    CSceneComponent *MainComponent;

    int32_t Width;
    int32_t Height;

    glm::vec2 PerlinLocation;
    float PerlinScale;
    float SphereFactor;

    CArray<CMeshComponent *> Spheres;
    CFDGrassMaterial *SphereMaterial;
    float SphereRadius;
    float Spacing;
    CMesh *SphereMesh;
};

#endif