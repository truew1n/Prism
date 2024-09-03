#include "SphereActor.hpp"
#include "MeshFactory.hpp"
#include "BaseMaterial.hpp"
#include "MainLevel.hpp"


CFDSphereActor::CFDSphereActor()
{
    YuccaAsset = CAssetLoader::LoadStatic("Assets\\Models\\Yucca\\model.obj");
    ZilAsset = CAssetLoader::LoadStatic("Assets\\Models\\Zil\\model.obj");

    Root = new CSceneComponent();

    for(CPair<CMesh *, CMaterial *> &Pair : YuccaAsset->AssetData) {
        CMesh *Mesh = Pair.GetFirst();
        CMaterial *Material = Pair.GetSecond();
        if(Mesh && Material) {
            CMeshComponent *TempMeshComponent = new CMeshComponent();
            Mesh->SetMaterial(Material);
            TempMeshComponent->SetMesh(Mesh);
            TempMeshComponent->SetLocalTransform(
                CTransform(
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f)
                )
            );
            Root->AddComponent(TempMeshComponent);
        }
    }
    
    TerrainComponent = new CMeshComponent();
    TerrainMaterial = new CFDBaseMaterial();
    TerrainMesh = CMeshFactory::GenerateTerrain(200, 200, 3.0f, 1.0f, 1, 1.0f, 2.0f);
    TerrainMesh->SetMaterial(TerrainMaterial);
    TerrainComponent->SetMesh(TerrainMesh);
    TerrainComponent->SetLocalTransform(
        CTransform(
            glm::vec3(-100.0f, 20.0f, -100.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0, 1.0f)
        )
    );

    for(CPair<CMesh *, CMaterial *> &Pair : ZilAsset->AssetData) {
        CMesh *Mesh = Pair.GetFirst();
        CMaterial *Material = Pair.GetSecond();
        if(Mesh && Material) {
            CMeshComponent *TempMeshComponent = new CMeshComponent();
            Mesh->SetMaterial(Material);
            TempMeshComponent->SetMesh(Mesh);
            TempMeshComponent->SetLocalTransform(
                CTransform(
                    glm::vec3(0.0f, 10.0f, 15.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f)
                )
            );
            Root->AddComponent(TempMeshComponent);
        }
    }
    Root->AddComponent(TerrainComponent);


    SphereComponent = new CMeshComponent();
    SphereMesh = CMeshFactory::GenerateSphere(5.0f, 32, 32);
    SphereMesh->SetMaterial(TerrainMaterial);
    SphereComponent->SetMesh(SphereMesh);
    SphereComponent->SetLocalTransform(
        CTransform(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        )
    );
    Root->AddComponent(SphereComponent);
    RootComponent = Root;

    RootComponent->RegisterComponents(this);
}

void CFDSphereActor::Tick(float DeltaTime)
{
    CActor::Tick(DeltaTime);
    
    CTransform *SphereTransform = SphereComponent->GetLocalTransformRef();
    SphereTransform->Rotate(10.0f * DeltaTime, 20.0f * DeltaTime, 10.0f * DeltaTime);
}

CFDSphereActor::~CFDSphereActor()
{
    for(CPair<CMesh *, CMaterial *> &Pair : YuccaAsset->AssetData) {
        delete Pair.GetFirst();
        delete Pair.GetSecond();
    }
    delete YuccaAsset;

    delete TerrainMaterial;
    delete TerrainMesh;

    for(CPair<CMesh *, CMaterial *> &Pair : ZilAsset->AssetData) {
        delete Pair.GetFirst();
        delete Pair.GetSecond();
    }
    delete ZilAsset;
    
    delete SphereMesh;
}