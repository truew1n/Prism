#ifndef PE_SCENE_COMPONENT_HPP
#define PE_SCENE_COMPONENT_HPP

#include "ActorComponent.hpp"
#include "Transform.hpp"
#include "Array.hpp"

class CSceneComponent : public CActorComponent {
private:
    CTransform Transform;
    CArray<CSceneComponent *> *Compontents;
public:
    CSceneComponent();
    virtual void Draw(CTransform RootTransform);
    ~CSceneComponent();

    CTransform GetTransform();
    void SetTransform(CTransform NewTransform);
};

#endif