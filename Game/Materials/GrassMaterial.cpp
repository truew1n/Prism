#include "GrassMaterial.hpp"


CFDGrassMaterial::CFDGrassMaterial()
{
    Shader->Create();
    Shader->Load("Engine\\Resource\\Default.vert", EShaderType::Vertex);
    Shader->Load("Engine\\Resource\\Default.frag", EShaderType::Fragment);

    GrassDiffuse = new CTexture("Assets\\Textures\\Grass\\Grass_2_Diffuse.jpg", "UDiffuse", 0);

    GrassDiffuse->SetTextureParameter(ETextureParameter::MinFilter, ETextureParameterValue::Nearest);
	GrassDiffuse->SetTextureParameter(ETextureParameter::MagFilter, ETextureParameterValue::Nearest);

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