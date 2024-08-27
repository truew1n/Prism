#ifndef PE_OBJECT_HPP
#define PE_OBJECT_HPP

#include "FunctionLibrary.hpp"

class CObject {
public:
    virtual void Tick(float DeltaTime);
};

#endif