#include "MeshComponent.hpp"
#include "PlayerController.hpp"
#include "Level.hpp"

CMeshComponent::CMeshComponent()
{

}

void CMeshComponent::Draw()
{
    if(Mesh) {
        CMaterial *MeshMaterial = Mesh->GetMaterial();
        if(MeshMaterial) {
            glm::mat4 ParentChildTransform = GetSetParentChildTransform();
            
            if(CActor *Owner = GetOwner()) {
                if(CLevel *Level = Owner->GetLevel()) {
                    if(CPlayerController *PlayerController = Level->GetPlayerController()) {
                        if(CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
                            if(CCamera *Camera = CameraComponent->GetCamera()) {
                                MeshMaterial->Bind();
                                MeshMaterial->SetProjection(Camera->GetProjectionMatrix());
                                MeshMaterial->SetView(Camera->GetViewMatrix(
                                    CameraComponent->GetWorldTransform(),
                                    CameraComponent->GetLocalTransform()
                                ));
                                MeshMaterial->SetTransform(ParentChildTransform);
                                Mesh->Draw();
                                MeshMaterial->Unbind();
                            }
                        }
                    }
                }
            }
        }
    }
}

CMeshComponent::~CMeshComponent()
{
    // It causes multiple frees, when mesh is shared
    // if(Mesh) {
    //     delete Mesh;
    // }
}

CMesh *CMeshComponent::GetMesh()
{
    return Mesh;
}

void CMeshComponent::SetMesh(CMesh *NewMesh)
{
    Mesh = NewMesh;
}