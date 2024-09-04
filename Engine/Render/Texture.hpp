#ifndef PE_TEXTURE_HPP
#define PE_TEXTURE_HPP

#include <GL/glew.h>
#include "Shader.hpp"
#include "stb_image.h"
#include "RenderObject.hpp"

enum class ETextureParameter : uint32_t {
	/*
		Possible values (ETextureParameterValue):
		- Nearest
		- Linear
		- NearestMipMapNearest
		- LinearMipMapNearest
		- NearestMipMapLinear
		- LinearMipMapLinear
	*/
	MinFilter = GL_TEXTURE_MIN_FILTER,
	/*
		Possible values (ETextureParameterValue):
		- Nearest
		- Linear
	*/
	MagFilter = GL_TEXTURE_MAG_FILTER,
	/*
		Possible values (ETextureParameterValue):
		- ClampToEdge
		- ClampToBorder
		- MirroredRepeat
		- Repeat
		- MirrorClampToEdge
	*/
	WrapU = GL_TEXTURE_WRAP_S,
	/*
		Possible values (ETextureParameterValue):
		- ClampToEdge
		- ClampToBorder
		- MirroredRepeat
		- Repeat
		- MirrorClampToEdge
	*/
	WrapV = GL_TEXTURE_WRAP_T
};

enum class ETextureParameterValue : int32_t {
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
	NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
	LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
	NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
	LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR,

	ClampToEdge = GL_CLAMP_TO_EDGE,
	ClampToBorder = GL_CLAMP_TO_BORDER,
	MirroredRepeat = GL_MIRRORED_REPEAT,
	Repeat = GL_REPEAT,
	MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
};

class CTexture : public RenderObject {
private:
	const char *Type;
	uint32_t Unit;
public:
	CTexture() : Type(nullptr), Unit(0) {};
	CTexture(const char *Image, const char *TextureType, uint32_t Slot);

	void SetUniform(CShader *Shader, const char *Uniform, uint32_t Unit);
	void SetTextureParameter(ETextureParameter Type, ETextureParameterValue Value);
	void Bind();
	void Unbind();
	void Delete();

	const char *GetType() { return Type; }
	uint32_t GetUnit() { return Unit; }
};

#endif