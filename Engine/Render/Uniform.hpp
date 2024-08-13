#ifndef PE_UNIFORM_HPP
#define PE_UNIFORM_HPP

#include <iostream>
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class CUniform {
private:
    static GLint GetUniformLocation(CShader *Shader, std::string Name);
public:
    template<typename T>
    static void SetUniform(CShader *Shader, std::string Name, T Value);
};

#endif
