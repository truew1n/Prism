#ifndef PE_SCENE_COMPONENT_HPP
#define PE_SCENE_COMPONENT_HPP

#include "ActorComponent.hpp"
#include "Transform.hpp"

class CSceneComponent : public CActorComponent {
private:
    CTransform Transform;
public:
    CTransform GetTransform();
};

#endif