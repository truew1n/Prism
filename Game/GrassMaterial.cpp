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

    Textures.Add(GrassDiffuse);

    CameraPosition = glm::vec3(0.0f);
    FogStart = 100.0f;
    FogEnd = 300.0f;
    FogColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

void CFDGrassMaterial::Bind()
{
    CMaterial::Bind();

    CUniform::SetUniform<glm::vec3>(Shader, "UCameraPosition", CameraPosition);
    CUniform::SetUniform<float>(Shader, "UFogStart", FogStart);
    CUniform::SetUniform<float>(Shader, "UFogEnd", FogEnd);
    CUniform::SetUniform<glm::vec3>(Shader, "UFogColor", FogColor);
}

void CFDGrassMaterial::Unbind()
{
    CMaterial::Unbind();

}

CFDGrassMaterial::~CFDGrassMaterial()
{

}