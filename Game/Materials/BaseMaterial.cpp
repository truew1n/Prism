#include "BaseMaterial.hpp"

CFDBaseMaterial::CFDBaseMaterial()
{
    Shader.Create();
    Shader.Load("Engine\\Resource\\Default.vert", EShaderType::VERTEX);
    Shader.Load("Engine\\Resource\\Default.frag", EShaderType::FRAGMENT);

    Textures.Add(CTexture("Assets\\Textures\\ddd.png", "Diffuse", 0));
}

void CFDBaseMaterial::Bind()
{
    CMaterial::Bind();
    
}

void CFDBaseMaterial::Unbind()
{
    CMaterial::Unbind();

}

void CFDBaseMaterial::Delete()
{
    CMaterial::Delete();
    
}