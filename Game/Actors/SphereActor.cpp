#include "SphereActor.hpp"
#include "MeshFactory.hpp"
#include "BaseMaterial.hpp"
#include "MainLevel.hpp"


CFDSphereActor::CFDSphereActor()
{
    YuccaAsset = CAssetLoader::LoadStatic("Assets\\Models\\Yucca\\model.obj");
    TerrainAsset = CAssetLoader::LoadStatic("Assets\\Models\\Terrain\\model.obj");
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
    
    for(CPair<CMesh *, CMaterial *> &Pair : TerrainAsset->AssetData) {
        CMesh *Mesh = Pair.GetFirst();
        CMaterial *Material = Pair.GetSecond();
        if(Mesh && Material) {
            CMeshComponent *TempMeshComponent = new CMeshComponent();
            Mesh->SetMaterial(Material);
            TempMeshComponent->SetMesh(Mesh);
            TempMeshComponent->SetLocalTransform(
                CTransform(
                    glm::vec3(0.0f, 0.0f, 5.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(10.0f, 10.0f, 10.0f)
                )
            );
            Root->AddComponent(TempMeshComponent);
        }
    }

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


    CMeshComponent *SphereComponent = new CMeshComponent();
    CMesh *SphereMesh = CMeshFactory::GenerateSphere(5.0f, 32, 32);
    SphereMesh->SetMaterial(new CFDBaseMaterial());
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
    
}

CFDSphereActor::~CFDSphereActor()
{
    for(CPair<CMesh *, CMaterial *> &Pair : YuccaAsset->AssetData) {
        delete Pair.GetFirst();
        delete Pair.GetSecond();
    }
    for(CPair<CMesh *, CMaterial *> &Pair : TerrainAsset->AssetData) {
        delete Pair.GetFirst();
        delete Pair.GetSecond();
    }
    for(CPair<CMesh *, CMaterial *> &Pair : ZilAsset->AssetData) {
        delete Pair.GetFirst();
        delete Pair.GetSecond();
    }
    delete YuccaAsset;
    delete TerrainAsset;
    delete ZilAsset;
}