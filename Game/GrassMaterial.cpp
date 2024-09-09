#include "GrassMaterial.h"


CFDGrassMaterial::CFDGrassMaterial()
{
    Shader->Create();
    Shader->Load("Assets\\Shaders\\Default.vert", EShaderType::Vertex);
    Shader->Load("Assets\\Shaders\\Default.frag", EShaderType::Fragment);

    GrassDiffuse = new CTexture("Assets\\Textures\\Grass\\Grass_2_Diffuse.jpg", "UDiffuse", 0);

    GrassDiffuse->SetTextureParameter(ETextureParameter::MinFilter, ETextureParameterValue::LinearMipMapLinear);
    GrassDiffuse->SetTextureParameter(ETextureParameter::MagFilter, ETextureParameterValue::Linear);

    GrassDiffuse->SetTextureParameter(ETextureParameter::WrapU, ETextureParameterValue::Repeat);
    GrassDiffuse->SetTextureParameter(ETextureParameter::WrapV, ETextureParameterValue::Repeat);

    Textures->Add(GrassDiffuse);
}

void CFDGrassMaterial::Bind()
{
    CMaterial::Bind();

}

void CFDGrassMaterial::Unbind()
{
    CMaterial::Unbind();

}

CFDGrassMaterial::~CFDGrassMaterial()
{

}