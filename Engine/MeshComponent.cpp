#include "MeshComponent.h"
#include "PlayerController.h"
#include "Level.h"

CMeshComponent::CMeshComponent()
{
    MMesh = nullptr;
    MCachedCameraComponent = nullptr;
}

void CMeshComponent::Tick(float DeltaTime)
{
    SetParentChildTransform();

    if (!MCachedCameraComponent) {
        if (CActor *Owner = GetOwner()) {
            if (CLevel *Level = Owner->GetLevel()) {
                if (CPlayerController *PlayerController = Level->GetPlayerController()) {
                    if (CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
                        MCachedCameraComponent = CameraComponent;
                    }
                }
            }
        }
    }
}

void CMeshComponent::Draw()
{
    if (!MMesh) return;

    CMaterial *MeshMaterial = MMesh->GetMaterial();
    if (!MeshMaterial) return;
    
    if (!MCachedCameraComponent) return;

    CCamera *Camera = MCachedCameraComponent->GetCamera();
    if (!Camera) return;

    glm::mat4 ProjectionMatrix = Camera->GetProjectionMatrix();
    glm::mat4 ViewMatrix = Camera->GetViewMatrix(
        MCachedCameraComponent->GetWorldTransform(),
        MCachedCameraComponent->GetLocalTransform()
    );
    glm::mat4 CameraMatrix = ProjectionMatrix * ViewMatrix;

    if (MMesh->HasBoundingVolume) {
        CBoundingVolume *BoundingVolume = MMesh->GetBoundingVolume();

        if (!BoundingVolume->InFrustum(&CameraMatrix, GetWorldTransformRef())) {
            std::cout << "Not In Frustum" << std::endl;
            return;
        } 
    }

    MeshMaterial->Bind();
    MeshMaterial->SetProjection(ProjectionMatrix);
    MeshMaterial->SetView(ViewMatrix);
    MeshMaterial->SetTransform(GetWorldTransform());
    MMesh->Draw();
    MeshMaterial->Unbind();
}

CMeshComponent::~CMeshComponent()
{
    // It causes multiple frees, when mesh is shared
    // if(MMesh) {
    //     delete MMesh;
    // }
}

CMesh *CMeshComponent::GetMesh()
{
    return MMesh;
}

void CMeshComponent::SetMesh(CMesh *NewMesh)
{
    MMesh = NewMesh;
}