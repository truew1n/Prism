#ifndef PE_SHADER_HPP
#define PE_SHADER_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "file.h"
#include "RenderObject.hpp"

enum class EShaderType : uint32_t {
    Vertex = GL_VERTEX_SHADER,
    TessellationControl = GL_TESS_CONTROL_SHADER,
    TessellationEvaluation = GL_TESS_EVALUATION_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    Compute = GL_COMPUTE_SHADER
};

class CShader : public RenderObject {
private:
    const char *MatchShaderTypeString(EShaderType Type);
public:
    uint32_t Compile(const char *Source, EShaderType Type);
    void Create();
    uint8_t Load(const char *Filepath, EShaderType Type);
    void Activate();
    void Deactivate();
    void Delete();
};

#endif