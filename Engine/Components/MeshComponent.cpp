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
            glm::mat4 NewTransformMatrix = glm::mat4(1.0f);
            if(CSceneComponent *Parent = GetParent()) {
                NewTransformMatrix = Parent->GetWorldTransform() * GetLocalTransform().GetTransformMatrix();
            } else {
                NewTransformMatrix = GetLocalTransform().GetTransformMatrix();
            }
            SetWorldTransform(NewTransformMatrix);

            bool dbgprint = false;

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
                                MeshMaterial->SetTransform(NewTransformMatrix);
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