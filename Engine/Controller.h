#ifndef PE_CONTROLLER_H
#define PE_CONTROLLER_H

#include "Actor.h"

class CController : public CActor {
public:
    CController();
    virtual void Tick(float DeltaTime) override;
    ~CController();
};

#endif