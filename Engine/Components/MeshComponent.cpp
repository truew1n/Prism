#include "MeshComponent.hpp"
#include "PlayerController.hpp"
#include "Level.hpp"

CMeshComponent::CMeshComponent()
{
    MMesh = nullptr;
    MCachedCameraComponent = nullptr;
}

void CMeshComponent::Tick(float DeltaTime)
{
    SetParentChildTransform();
    
    if(!MCachedCameraComponent) {
        if(CActor *Owner = GetOwner()) {
            if(CLevel *Level = Owner->GetLevel()) {
                if(CPlayerController *PlayerController = Level->GetPlayerController()) {
                    if(CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
                        MCachedCameraComponent = CameraComponent;
                    }
                }
            }
        }
    }
}

void CMeshComponent::Draw()
{
    if(MMesh) {
        CMaterial *MeshMaterial = MMesh->GetMaterial();
        if(MeshMaterial) {
            if(MCachedCameraComponent) {
                if(CCamera *Camera = MCachedCameraComponent->GetCamera()) {
                    MeshMaterial->Bind();
                    MeshMaterial->SetProjection(Camera->GetProjectionMatrix());
                    MeshMaterial->SetView(Camera->GetViewMatrix(
                        MCachedCameraComponent->GetWorldTransform(),
                        MCachedCameraComponent->GetLocalTransform()
                    ));
                    MeshMaterial->SetTransform(GetWorldTransform());
                    MMesh->Draw();
                    MeshMaterial->Unbind();
                }
            }
        }
    }
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