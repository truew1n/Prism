#ifndef PE_TEXTURE_HPP
#define PE_TEXTURE_HPP

#include <GL/glew.h>
#include "Shader.hpp"
#include "stb_image.h"
#include "RenderObject.hpp"

class CTexture : public RenderObject {
private:
	const char *Type;
	uint32_t Unit;
public:
	CTexture() : Type(nullptr), Unit(0) {};
	CTexture(const char *Image, const char *TextureType, uint32_t Slot);

	void SetUniform(CShader *Shader, const char *Uniform, uint32_t Unit);
	void Bind();
	void Unbind();
	void Delete();

	const char *GetType() { return Type; }
	uint32_t GetUnit() { return Unit; }
};

#endif