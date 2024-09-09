#include "BaseMaterial.h"

CFDBaseMaterial::CFDBaseMaterial()
{
    Shader->Create();
    Shader->Load("Assets\\Shaders\\Default.vert", EShaderType::Vertex);
    Shader->Load("Assets\\Shaders\\Default.frag", EShaderType::Fragment);

    Textures->Add(new CTexture("Assets\\Textures\\autumn_field_puresky.jpg", "UDiffuse", 0));
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