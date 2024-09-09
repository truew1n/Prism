#ifndef PE_MATERIAL_H
#define PE_MATERIAL_H

#include "Shader.h"
#include "Texture.h"
#include "Uniform.h"
#include "Transform.h"
#include "Array.h"

class CMaterial {
protected:
    CShader *Shader;
    CArray<CTexture *> *Textures;
public:
    CMaterial();
    virtual void Bind();
    virtual void Unbind();
    virtual ~CMaterial();

    CShader *GetShader() const { return Shader; }
    void AddTexture(CTexture *Texture);

    virtual void SetProjection(glm::mat4 Projection);
    virtual void SetView(glm::mat4 View);
    virtual void SetTransform(CTransform Transform);
    virtual void SetTransform(glm::mat4 TransformMatrix);
};

#endif