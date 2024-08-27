#include "Material.hpp"


CMaterial::CMaterial()
{
    Shader = new CShader();
    Textures = new CArray<CTexture *>();
}

void CMaterial::Bind()
{
    Shader->Activate();
    for(int32_t I = 0; I < Textures->Num(); ++I) {
        CTexture *Texture = Textures->Get(I);
        Texture->SetUniform(Shader, Texture->GetType(), Texture->GetUnit());
        Texture->Bind();
    }
}

void CMaterial::Unbind()
{
    Shader->Deactivate();
    for(int32_t I = 0; I < Textures->Num(); ++I) {
        CTexture *Texture = Textures->Get(I);
        Texture->Unbind();
    }
}

CMaterial::~CMaterial()
{
    Shader->Delete();
    delete Shader;
    for(int32_t I = 0; I < Textures->Num(); ++I) {
        CTexture *Texture = Textures->Get(I);
        Texture->Delete();
    }
    delete Textures;
}

void CMaterial::SetProjection(glm::mat4 Projection)
{
    CUniform::SetUniform<glm::mat4>(Shader, "Projection", Projection);
}

void CMaterial::SetView(glm::mat4 View)
{
    CUniform::SetUniform<glm::mat4>(Shader, "View", View);
}

void CMaterial::SetTransform(CTransform Transform)
{
    glm::mat4 TransformMatrix = Transform.GetTransformMatrix();

    CUniform::SetUniform<glm::mat4>(Shader, "Transform", TransformMatrix);
}

void CMaterial::SetTransform(glm::mat4 TransformMatrix)
{
    CUniform::SetUniform<glm::mat4>(Shader, "Transform", TransformMatrix);
}