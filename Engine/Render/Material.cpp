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
    for(int32_t I = 0; I < Textures->Num(); ++I) {
        CTexture *Texture = Textures->Get(I);
        Texture->Unbind();
    }
}

CMaterial::~CMaterial()
{
    delete Shader;
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

void CMaterial::SetWorldPosition(glm::vec3 WorldPosition)
{
    CUniform::SetUniform<glm::vec3>(Shader, "WorldPosition", WorldPosition);

}