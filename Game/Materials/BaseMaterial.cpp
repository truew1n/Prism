#include "BaseMaterial.hpp"

CFDBaseMaterial::CFDBaseMaterial()
{
    Shader->Create();
    Shader->Load("Engine\\Resource\\Default.vert", EShaderType::VERTEX);
    Shader->Load("Engine\\Resource\\Default.frag", EShaderType::FRAGMENT);

    Textures->Add(new CTexture("Assets\\Textures\\Rock\\Rock13_4K_BaseColor.png", "Diffuse", 0));
    Textures->Add(new CTexture("Assets\\Textures\\Rock\\Rock13_4K_Normal.png", "Normal", 1));
}

void CFDBaseMaterial::Bind()
{
    CMaterial::Bind();
    
}

void CFDBaseMaterial::Unbind()
{
    CMaterial::Unbind();

}

CFDBaseMaterial::~CFDBaseMaterial()
{
    
}