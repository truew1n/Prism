#ifndef PE_VERTEX_BUFFER_HPP
#define PE_VERTEX_BUFFER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Array.hpp"

typedef struct SVertex {
	glm::vec3 Position;
	glm::vec2 UV;

	SVertex() : Position(glm::vec3(0.0f, 0.0f, 0.0f)), UV(glm::vec2(0.0f, 0.0f)) {}
	SVertex(glm::vec3 Position, glm::vec2 UV) : Position(Position), UV(UV) {}
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