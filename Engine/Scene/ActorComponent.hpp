#ifndef PE_ACTOR_COMPONENT_HPP
#define PE_ACTOR_COMPONENT_HPP

#include "Object.hpp"

class CActor;

class CActorComponent : public CObject {
private:
    CActor *Owner;
public:
    CActorComponent();
    CActor *GetOwner();
    void Tick(float DeltaTime) override;
    ~CActorComponent();
};

#endif