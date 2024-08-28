#ifndef PE_VERTEX_BUFFER_HPP
#define PE_VERTEX_BUFFER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Array.hpp"

typedef struct SVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;

	SVertex() : Position(0.0f), Normal(0.0f), UV(0.0f) {}
	SVertex(glm::vec3 IPosition, glm::vec2 IUV) : Position(IPosition), Normal(0.0f), UV(IUV) {}
	SVertex(glm::vec3 IPosition, glm::vec3 INormal, glm::vec2 IUV) : Position(IPosition), Normal(INormal), UV(IUV) {}
} SVertex;

class CVertexBuffer {
public:
    uint32_t Id;

    CVertexBuffer(CArray<SVertex> *Vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif