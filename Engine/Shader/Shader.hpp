#ifndef PE_SHADER_HPP
#define PE_SHADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "file.h"
#include "RenderObject.hpp"

enum class EShaderType : uint8_t {
    VERTEX,
    TESSELLATION_CONTROL,
    TESSELLATION_EVALUATION,
    GEOMETRY,
    FRAGMENT,
    COMPUTE
};

class CShader : public RenderObject {
private:
    uint32_t MatchShaderType(EShaderType Type);
    const char *GLTypeToString(uint32_t GLType);
public:
    uint32_t Compile(const char *Source, EShaderType Type);
    void Create();
    uint8_t Load(const char *Filepath, EShaderType Type);
    void Activate();
    void Deactivate();
    void Delete();
};

#endif