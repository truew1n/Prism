#ifndef PE_VERTEX_ARRAY_H
#define PE_VERTEX_ARRAY_H

#include <GL/glew.h>
#include "VertexBuffer.h"
#include "RenderObject.h"

class CVertexArray : public CRenderObject {
public:
	CVertexArray();

	void LinkAttribute(CVertexBuffer *VertexBuffer, uint32_t Layout, uint32_t ComponentCount, uint32_t Type, ptrdiff_t Stride, void *Offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif