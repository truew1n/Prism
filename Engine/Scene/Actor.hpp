#ifndef PE_ACTOR_HPP
#define PE_ACTOR_HPP

#include "Object.hpp"
#include "SceneComponent.hpp"
#include "Transform.hpp"

class CActor : public CObject {
public:
    CSceneComponent *RootComponent;

    CActor();
    void Draw();
    void Tick(float DeltaTime);
    ~CActor();

    CTransform GetTransform();
    void SetTransform(CTransform NewTransform);
};

#endif