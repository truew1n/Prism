#ifndef PE_ACTOR_COMPONENT_HPP
#define PE_ACTOR_COMPONENT_HPP

#include "Object.hpp"

class CActor;

class CActorComponent : public CObject {
protected:
    CActor *Owner;
public:
    CActorComponent();
    virtual void Tick(float DeltaTime) override;
    ~CActorComponent();

    CActor *GetOwner();
    void SetOwner(CActor *NewOwner);
};

#endif