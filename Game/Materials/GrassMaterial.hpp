#ifndef CFD_GRASS_MATERIAL_HPP
#define CFD_GRASS_MATERIAL_HPP

#include "Material.hpp"

class CFDGrassMaterial : public CMaterial {
public:
    CFDGrassMaterial();
    virtual void Bind() override;
    virtual void Unbind() override;
    ~CFDGrassMaterial() override;

    CTexture *GrassDiffuse;
};

#endif