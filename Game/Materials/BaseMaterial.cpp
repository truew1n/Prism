#include "BaseMaterial.hpp"

CFDBaseMaterial::CFDBaseMaterial()
{
    Shader->Create();
    Shader->Load("Engine\\Resource\\Default.vert", EShaderType::VERTEX);
    Shader->Load("Engine\\Resource\\Default.frag", EShaderType::FRAGMENT);

    Textures->Add(new CTexture("Assets\\Textures\\Rust\\SpaceLabWallOld_albedo.png", "UDiffuse", 0));
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