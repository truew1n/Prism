#ifndef CFD_BASEMATERIAL_HPP
#define CFD_BASEMATERIAL_HPP

#include "Material.hpp"

class CFDBaseMaterial : public CMaterial {
public:
    CFDBaseMaterial();
    virtual void Bind() override;
    virtual void Unbind() override;
    virtual void Delete() override;
};

#endif