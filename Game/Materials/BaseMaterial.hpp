#ifndef CFD_BASE_MATERIAL_HPP
#define CFD_BASE_MATERIAL_HPP

#include "Material.hpp"

class CFDBaseMaterial : public CMaterial {
public:
    CFDBaseMaterial();
    virtual void Bind() override;
    virtual void Unbind() override;
    ~CFDBaseMaterial() override;
};

#endif