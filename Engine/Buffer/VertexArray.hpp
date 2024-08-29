#ifndef PE_VERTEX_ARRAY_HPP
#define PE_VERTEX_ARRAY_HPP

#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include "RenderObject.hpp"

class CVertexArray : public RenderObject {
public:
	CVertexArray();

	void LinkAttribute(CVertexBuffer *VertexBuffer, uint32_t Layout, uint32_t ComponentCount, uint32_t Type, ptrdiff_t Stride, void *Offset);
	void Bind();
	void Unbind();
	void Delete();
};
    
#endif