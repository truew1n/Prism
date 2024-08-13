#include "BaseMaterial.hpp"

CFDBaseMaterial::CFDBaseMaterial()
{
    Shader = new CShader();
    Shader->Create();
    Shader->Load("Engine\\Resource\\Default.vert", EShaderType::VERTEX);
    Shader->Load("Engine\\Resource\\Default.frag", EShaderType::FRAGMENT);

    Textures->Add(new CTexture("Assets\\Textures\\ddd.png", "Diffuse", 0));
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
    Shader->Delete();
    delete Shader;
    for(int32_t I = 0; I < Textures->Num(); ++I) {
        CTexture *Texture = Textures->Get(I);
        Texture->Delete();
    }
    delete Textures;
}