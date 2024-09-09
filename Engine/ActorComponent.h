#ifndef PE_ACTOR_COMPONENT_H
#define PE_ACTOR_COMPONENT_H

#include "Object.h"

class CActor;

class CActorComponent : public CObject {
protected:
    CActor *Owner;
public:
    CActorComponent();
    virtual void Tick(float DeltaTime) override;
    ~CActorComponent() override;

    CActor *GetOwner();
    void SetOwner(CActor *NewOwner);
};

#endif