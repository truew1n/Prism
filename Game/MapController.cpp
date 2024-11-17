#include "MapController.h"
#include "MainLevel.h"
#include "MeshFactory.h"
#include "GrassMaterial.h"
#include "FunctionLibrary.h"

#include "AssetLoader.h"

bool MeshComparator(CMeshComponent *First, CMeshComponent *Second)
{
    if (!(First || Second)) return false;
    if (!First->GetCachedCameraComponent()) return false;

    glm::vec3 CameraLocation = First->GetCachedCameraComponent()->GetWorldTransform() * glm::vec4(1.0f);

    float FirstDistance = glm::distance(CameraLocation, glm::vec3(First->GetWorldTransform() * glm::vec4(1.0f)));
    float SecondDistance = glm::distance(CameraLocation, glm::vec3(Second->GetWorldTransform() * glm::vec4(1.0f)));

    return FirstDistance < SecondDistance;
}

GMapController::GMapController()
{
    Controller = new CPlayerController();
    CachedCameraComponent = nullptr;

    if (CLevel *Level = GetLevel()) {
        if (CPlayerController *PlayerController = Level->GetPlayerController()) {
            if (CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
                CachedCameraComponent = CameraComponent;
            }
        }
    }

    YuccaAsset = CAssetLoader::LoadStatic("Assets\\Models\\GTA_SA_PART1\\GTA_SA_PART1.fbx");

    CMesh *TempMesh = nullptr;
    CMaterial *TempMaterial = nullptr;
    for (CPair<CMesh *, CMaterial *> Pair : YuccaAsset->AssetData) {
        CMeshComponent *TempMeshComponent = new CMeshComponent();
        TempMesh = Pair.GetFirst();
        TempMaterial = Pair.GetSecond();

        TempMesh->SetMaterial(TempMaterial);
        TempMeshComponent->SetMesh(TempMesh);
        TempMeshComponent->GetLocalTransformRef()->RotateX(-90.0f);
        TempMeshComponent->SetOwner(this);
        if (CTexture *TempTexture = TempMaterial->GetTexture(0)) {
            if (TempTexture->GetType() == ETextureType::Diffuse) {
                if (TempTexture->GetChannels() == 4) {
                    TransparentObjects.Add(TempMeshComponent);
                } else {
                    OpaqueObjects.Add(TempMeshComponent);
                }
            }
        }
    }
}

void GMapController::Draw()
{
    /*
    * Default Drawing
    
    if (RootComponent) {
        RootComponent->Draw();
    }*/
    for (CMeshComponent *MeshComponent : OpaqueObjects) {
        /*glm::vec3 TransformedCentroid = MeshComponent->GetWorldTransform() * glm::vec4(MeshComponent->GetMesh()->GetBoundingVolume()->GetCentroid(), 1.0f);
        glm::vec3 CameraLocation = MeshComponent->GetCachedCameraComponent()->GetWorldTransform() * glm::vec4(1.0f);
        if (glm::distance(CameraLocation, TransformedCentroid) < 200) {
            MeshComponent->Draw();
        }*/
        MeshComponent->Draw();
    }

    for (CMeshComponent *MeshComponent : TransparentObjects) {
        /*glm::vec3 TransformedCentroid = MeshComponent->GetWorldTransform() * glm::vec4(MeshComponent->GetMesh()->GetBoundingVolume()->GetCentroid(), 1.0f);
        glm::vec3 CameraLocation = MeshComponent->GetCachedCameraComponent()->GetWorldTransform() * glm::vec4(1.0f);
        if (glm::distance(CameraLocation, TransformedCentroid) < 200) {
            MeshComponent->Draw();
        }*/
        MeshComponent->Draw();
    }
}

void GMapController::Tick(float DeltaTime)
{
    for (CMeshComponent *MeshComponent : OpaqueObjects) {
        MeshComponent->Tick(DeltaTime);
    }

    for (CMeshComponent *MeshComponent : TransparentObjects) {
        MeshComponent->Tick(DeltaTime);
    }

    //TransparentObjects.Sort(&MeshComparator);
}

GMapController::~GMapController()
{
    for (CPair<CMesh *, CMaterial *> Pair : YuccaAsset->AssetData) {
        delete Pair.GetFirst();
        delete Pair.GetSecond();
    }

    delete YuccaAsset;
}
