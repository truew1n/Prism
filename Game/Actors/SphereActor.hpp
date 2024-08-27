#ifndef CFD_SPHERE_ACTOR_HPP
#define CFD_SPHERE_ACTOR_HPP

#include "Actor.hpp"
#include "MeshComponent.hpp"

class CFDSphereActor : public CActor {
public:
    CFDSphereActor();
    void Tick(float DeltaTime) override;
    ~CFDSphereActor();

    CMeshComponent *SphereMeshComponent;
    CMesh *SphereMesh;
    CMaterial *SphereMaterial;
};

#endif