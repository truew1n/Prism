#ifndef PE_VERTEX_BUFFER_H
#define PE_VERTEX_BUFFER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Array.h"
#include "RenderObject.h"

typedef struct SVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;

	SVertex() : Position(0.0f), Normal(0.0f), UV(0.0f) {}
	SVertex(glm::vec3 IPosition, glm::vec2 IUV) : Position(IPosition), Normal(0.0f), UV(IUV) {}
	SVertex(glm::vec3 IPosition, glm::vec3 INormal, glm::vec2 IUV) : Position(IPosition), Normal(INormal), UV(IUV) {}
} SVertex;

class CVertexBuffer : public CRenderObject {
public:
	CVertexBuffer(CArray<SVertex> *Vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif