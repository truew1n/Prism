#ifndef PE_OBJECT_H
#define PE_OBJECT_H

#include "FunctionLibrary.h"

class CObject {
public:
    CObject();
    virtual void Tick(float DeltaTime);
    virtual ~CObject();
};

#endif