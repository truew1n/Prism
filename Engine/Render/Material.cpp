#include "Material.hpp"


CMaterial::CMaterial()
{
    // ;;
}

void CMaterial::Bind()
{
    Shader.Activate();
    for(CTexture Texture : Textures) {
        Texture.SetUniform(Shader, Texture.GetType(), Texture.GetUnit());
        Texture.Bind();
    }
}

void CMaterial::Unbind()
{
    for(CTexture Texture : Textures) {
        Texture.Unbind();
    }
}

void CMaterial::Delete()
{
    Textures.Free();
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