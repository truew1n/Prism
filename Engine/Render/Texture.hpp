#ifndef PE_TEXTURE_HPP
#define PE_TEXTURE_HPP

#include <GL/glew.h>
#include "Shader.hpp"
#include "stb_image.h"

class CTexture {
private:
	uint32_t Id;
	const char *Type;
	uint32_t Unit;
public:
	CTexture() : Id(0), Type(nullptr), Unit(0) {};
	CTexture(const char *Image, const char *TextureType, uint32_t Slot);

	void SetUniform(CShader *Shader, const char *Uniform, uint32_t Unit);
	void Bind();
	void Unbind();
	void Delete();

	uint32_t GetId() { return Id; }
	const char *GetType() { return Type; }
	uint32_t GetUnit() { return Unit; }
};

#endif