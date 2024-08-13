#ifndef PE_MATERIAL_HPP
#define PE_MATERIAL_HPP

#include "Shader.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"
#include "Array.hpp"

class CMaterial {
protected:
    CShader *Shader;
    CArray<CTexture*> *Textures;
public:
    CMaterial();
    virtual void Bind();
    virtual void Unbind();
    ~CMaterial();

    virtual void SetProjection(glm::mat4 Projection);
    virtual void SetView(glm::mat4 View);
    virtual void SetWorldPosition(glm::vec3 WorldPosition);
};

#endif