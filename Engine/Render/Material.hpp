#ifndef PE_MATERIAL_HPP
#define PE_MATERIAL_HPP

#include "Shader.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"
#include "Transform.hpp"
#include "Array.hpp"

class CMaterial {
protected:
    CShader *Shader;
    CArray<CTexture *> *Textures;
public:
    CMaterial();
    virtual void Bind();
    virtual void Unbind();
    virtual ~CMaterial();

    virtual void SetProjection(glm::mat4 Projection);
    virtual void SetView(glm::mat4 View);
    virtual void SetTransform(CTransform Transform);
    virtual void SetTransform(glm::mat4 TransformMatrix);
};

#endif