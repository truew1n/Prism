#ifndef PE_CONTROLLER_HPP
#define PE_CONTROLLER_HPP

#include "Actor.hpp"

class CController : public CActor {
public:
    CController();
    virtual void Tick(float DeltaTime) override;
    ~CController();
};

#endif