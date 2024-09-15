#include "MainLevel.h"
#include "Player.h"
#include "PerlinGrid.h"
#include "MeshFactory.h"
#include "BaseMaterial.h"

#include "AssetLoader.h"
#include "Pair.h"
#include "CuboidBoundingVolume.h"

CFDMainLevel::CFDMainLevel()
{
    LastX = 0.0;
    LastY = 0.0;

    YuccaAsset = CAssetLoader::LoadStatic("Assets\\Models\\Yucca\\model.obj");
    for (CPair<CMesh *, CMaterial *> Pair : YuccaAsset->AssetData) {
        Pair.GetFirst()->SetMaterial(Pair.GetSecond());
    }


    Player = new CFDPlayer();
    PerlinGrid = new CFDPerlinGrid();

    AddActor(Player);
    AddActor(PerlinGrid);

    SetPlayerController(Cast<CPlayerController *>(Player->GetController()));
}

#include "iomanip"

void CFDMainLevel::Tick(float DeltaTime)
{
    CLevel::Tick(DeltaTime);

    glm::mat4 TransformMatrix = glm::mat4(1.0f);
    TransformMatrix = glm::translate(TransformMatrix, glm::vec3(0.0f, 20.0f, 0.0f));
    for (CPair<CMesh *, CMaterial *> Pair : YuccaAsset->AssetData) {
        CMaterial *MeshMaterial = Pair.GetFirst()->GetMaterial();
        if (MeshMaterial) {
            if (CCameraComponent *MCachedCameraComponent = GetPlayerController()->GetCameraComponent()) {
                if (CCamera *Camera = MCachedCameraComponent->GetCamera()) {
                    glm::mat4 ProjectionMatrix = Camera->GetProjectionMatrix();
                    glm::mat4 ViewMatrix = Camera->GetViewMatrix(
                        MCachedCameraComponent->GetWorldTransform(),
                        MCachedCameraComponent->GetLocalTransform()
                    );
                    
                    glm::mat4 CameraMatrix = ProjectionMatrix * ViewMatrix;
                    CCuboidBoundingVolume *BoundingVolume = Cast<CCuboidBoundingVolume *>(Pair.GetFirst()->GetBoundingVolume());
                    
                    if (BoundingVolume->InFrustum(&CameraMatrix, &TransformMatrix)) {
                        CMesh *BoundingVolumeMesh = CMeshFactory::GenerateCuboid(
                            BoundingVolume->GetMinimum(), BoundingVolume->GetMaximum()
                        );

                        BoundingVolumeMesh->SetMaterial(MeshMaterial);

                        MeshMaterial->Bind();
                        MeshMaterial->SetProjection(Camera->GetProjectionMatrix());
                        MeshMaterial->SetView(Camera->GetViewMatrix(
                            MCachedCameraComponent->GetWorldTransform(),
                            MCachedCameraComponent->GetLocalTransform()
                        ));
                        MeshMaterial->SetTransform(TransformMatrix);
                        Pair.GetFirst()->Draw();
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        BoundingVolumeMesh->Draw();
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        MeshMaterial->Unbind();
                    }
                }
            }
        }
    }
}

CFDMainLevel::~CFDMainLevel()
{
    for (CPair<CMesh *, CMaterial *> Pair : YuccaAsset->AssetData) {
        delete Pair.GetFirst();
        delete Pair.GetSecond();
    }
    delete YuccaAsset;
}

void CFDMainLevel::MouseCallback(double X, double Y)
{
    float XOffset = (float)(X - LastX);
    float YOffset = (float)(LastY - Y);

    LastX = X;
    LastY = Y;

    float Sensitivity = 0.1f;
    XOffset *= Sensitivity;
    YOffset *= Sensitivity;

    if (CPlayerController *PlayerController = GetPlayerController()) {
        if (CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
            if (CCamera *Camera = CameraComponent->GetCamera()) {
                Camera->SetYaw(Camera->GetYaw() + XOffset);
                Camera->SetPitch(Camera->GetPitch() + YOffset);

                if (Camera->GetPitch() > 89.9f) {
                    Camera->SetPitch(89.9f);
                }
                if (Camera->GetPitch() < -89.9f) {
                    Camera->SetPitch(-89.9f);
                }
            }
        }
    }
}

void CFDMainLevel::ResizeCallback(int32_t Width, int32_t Height)
{
    if (CPlayerController *PlayerController = GetPlayerController()) {
        if (CCameraComponent *CameraComponent = PlayerController->GetCameraComponent()) {
            if (CCamera *Camera = CameraComponent->GetCamera()) {
                float AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
                Camera->SetAspectRatio(AspectRatio);
            }
        }
    }
}