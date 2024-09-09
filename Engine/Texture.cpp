#include "Texture.h"
#include <iostream>


CTexture::CTexture(const char *ITexturePath, const char *IUniformName, uint32_t ISlot)
{
	MUniformName = IUniformName;

	int32_t TextureWidth, TextureHeight, TextureChannels;
	stbi_set_flip_vertically_on_load(true);
	uint8_t *TextureData = stbi_load(ITexturePath, &TextureWidth, &TextureHeight, &TextureChannels, 0);

	glGenTextures(1, &Id);

	glActiveTexture(GL_TEXTURE0 + ISlot);
	MUnit = ISlot;
	glBindTexture(GL_TEXTURE_2D, Id);

	SetTextureParameter(ETextureParameter::MinFilter, ETextureParameterValue::LinearMipMapLinear);
	SetTextureParameter(ETextureParameter::MagFilter, ETextureParameterValue::Linear);

	SetTextureParameter(ETextureParameter::WrapU, ETextureParameterValue::Repeat);
	SetTextureParameter(ETextureParameter::WrapV, ETextureParameterValue::Repeat);

	if (TextureChannels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureWidth, TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureData);
	}
	else if (TextureChannels == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureWidth, TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
	}
	else if (TextureChannels == 1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, TextureWidth, TextureHeight, 0, GL_RED, GL_UNSIGNED_BYTE, TextureData);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(TextureData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CTexture::SetUniform(CShader *Shader)
{
	uint32_t TextureLocation = glGetUniformLocation(Shader->GetId(), MUniformName);

	glUniform1i(TextureLocation, MUnit);
}

void CTexture::SetTextureParameter(ETextureParameter Type, ETextureParameterValue Value)
{
	glTexParameteri(GL_TEXTURE_2D, (GLenum)Type, (GLint)Value);
}

void CTexture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + MUnit);
	glBindTexture(GL_TEXTURE_2D, Id);
}

void CTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CTexture::Delete()
{
	glDeleteTextures(1, &Id);
}