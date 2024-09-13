#include "PerlinGrid.h"
#include "MainLevel.h"
#include "MeshFactory.h"
#include "GrassMaterial.h"

CFDPerlinGrid::CFDPerlinGrid()
{
    Controller = new CPlayerController();
    MainComponent = new CSceneComponent();

    Width = 40;
    Height = 40;

    PerlinLocation = glm::vec2(0.0f, 0.0f);
    PerlinScale = 0.07f;
    SphereFactor = 3.0f;
    Spheres.Resize(Width * Height);

    SphereRadius = 0.1f;
    SphereMaterial = new CFDGrassMaterial();
    SphereMesh = CMeshFactory::GenerateCube(SphereRadius);
    SphereMesh->SetMaterial(SphereMaterial);

    float Spacing = SphereRadius;

    int32_t HalfWidth = Width / 2;
    int32_t HalfHeight = Height / 2;
    int32_t ModWidth = Width % 2;
    int32_t ModHeight = Height % 2;

    for (int32_t I = -HalfHeight; I < HalfHeight + ModHeight; ++I) {
        for (int32_t J = -HalfWidth; J < HalfWidth + ModWidth; ++J) {
            CMeshComponent *TempMeshComponent = new CMeshComponent();
            TempMeshComponent->SetMesh(SphereMesh);
            CTransform *CurrentTransform = TempMeshComponent->GetLocalTransformRef();
            CurrentTransform->Translate(
                glm::vec3(
                    Spacing * I,
                    0.0f,
                    Spacing * J
                )
            );
            Spheres.Set(
                TempMeshComponent,
                (I + HalfWidth) + (J + HalfHeight) * Width
            );
            MainComponent->AddComponent(TempMeshComponent);
        }
    }

    RootComponent = MainComponent;
    RootComponent->RegisterComponents(this);
}

void CFDPerlinGrid::Tick(float DeltaTime)
{
    CActor::Tick(DeltaTime);

    for (CMeshComponent *MeshComponent : Spheres) {
        CTransform *CurrentTransform = MeshComponent->GetLocalTransformRef();
        glm::vec3 CurrentLocation = CurrentTransform->GetLocation();

        float NewY = powf(glm::perlin(
            glm::vec2(
                (CurrentLocation.x + PerlinLocation.x) * PerlinScale,
                (CurrentLocation.z + PerlinLocation.y) * PerlinScale
            )
        ) * SphereFactor, 2.0f);

        CurrentTransform->SetLocation(glm::vec3(CurrentLocation.x, NewY, CurrentLocation.z));
    }

    PerlinLocation += glm::vec2(3.0f * DeltaTime, 0.0f);
}

CFDPerlinGrid::~CFDPerlinGrid()
{
    delete SphereMaterial;
    delete SphereMesh;
}
