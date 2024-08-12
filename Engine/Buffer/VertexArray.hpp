#ifndef PE_VERTEX_ARRAY_HPP
#define PE_VERTEX_ARRAY_HPP

#include <GL/glew.h>
#include "VertexBuffer.hpp"

class CVertexArray {
public:
	uint32_t Id;

	CVertexArray();

	void LinkAttribute(CVertexBuffer &VertexBuffer, uint32_t Layout, uint32_t ComponentCount, uint32_t Type, ptrdiff_t Stride, void *Offset);
	void Bind();
	void Unbind();
	void Delete();
};
    
#endif