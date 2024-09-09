#ifndef CFD_BASE_MATERIAL_H
#define CFD_BASE_MATERIAL_H

#include "Material.h"

class CFDBaseMaterial : public CMaterial {
public:
    CFDBaseMaterial();
    virtual void Bind() override;
    virtual void Unbind() override;
    ~CFDBaseMaterial() override;
};

#endif