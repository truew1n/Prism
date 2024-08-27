#include "SphereActor.hpp"
#include "MeshFactory.hpp"
#include "BaseMaterial.hpp"
#include "MainLevel.hpp"


CFDSphereActor::CFDSphereActor()
{
    SphereMeshComponent = new CMeshComponent();
    SphereMesh = CMeshFactory::GenerateSphere(10.0f, 32, 32);
    SphereMaterial = new CFDBaseMaterial();
    SphereMesh->SetMaterial(SphereMaterial);
    SphereMeshComponent->SetMesh(SphereMesh);
    SphereMeshComponent->SetLocalTransform(
        CTransform(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        )
    );

    RootComponent = SphereMeshComponent;

    RootComponent->RegisterComponents(this);
}

void CFDSphereActor::Tick(float DeltaTime)
{
    CActor::Tick(DeltaTime);
    
    CTransform *Transform = GetTransformRef();
    Transform->RotateX(10.0f * DeltaTime);
}

CFDSphereActor::~CFDSphereActor()
{
    delete SphereMesh;
    delete SphereMaterial;
}