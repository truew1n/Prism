#ifndef CFD_GRASS_MATERIAL_H
#define CFD_GRASS_MATERIAL_H

#include "Material.h"

class CFDGrassMaterial : public CMaterial {
public:
    CFDGrassMaterial();
    virtual void Bind() override;
    virtual void Unbind() override;
    ~CFDGrassMaterial() override;

    CTexture *GrassDiffuse;
};

#endif