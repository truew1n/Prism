#include "MeshComponent.hpp"

CMeshComponent::CMeshComponent()
{

}

void CMeshComponent::Draw(CTransform RootTransform)
{
    if(Mesh) {
        CMaterial *MeshMaterial = Mesh->GetMaterial();
        if(MeshMaterial) {
            MeshMaterial->SetWorldPosition(RootTransform.GetLocation());
            Mesh->Draw();
        }
    }
}

CMeshComponent::~CMeshComponent()
{
    if(Mesh) {
        delete Mesh;
    }
}

CMesh *CMeshComponent::GetMesh()
{
    return Mesh;
}

void CMeshComponent::SetMesh(CMesh *NewMesh)
{
    Mesh = NewMesh;
}