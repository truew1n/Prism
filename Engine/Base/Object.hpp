#ifndef PE_OBJECT_HPP
#define PE_OBJECT_HPP

#include "FunctionLibrary.hpp"

class CObject {
public:
    CObject();
    virtual void Tick(float DeltaTime);
    virtual ~CObject();
};

#endif